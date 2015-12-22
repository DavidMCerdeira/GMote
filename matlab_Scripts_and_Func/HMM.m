classdef HMM < handle
    properties
        name  = 'undefined';
        %Main properties
        N     = [];  % number of states
        M     = []; % number of features
        A     = []; % NxN transition probability matrixgit co
        b     = []; % NxM mean vector (D = number of features)
        pi    = []; % Nx1 initial state distribution vector
        
        %codebook
        codebook;
        codeData;
        
        %aproximate
        Anum     = [];
        Aden     = [];
        bnum     = [];
        bden     = [];
        P        = [];
        
        maxIters = [];
        
        %functionality
        scaling = 1;
        
    end
    
    methods
        function self = HMM(name, numOfStates, codebookSize, m, maxiter)
            self.name = name;
            self.N = numOfStates;
            self.M = codebookSize;
            self.codeData = m;
            self.codebook = KDTreeSearcher(m);
            self.maxIters = maxiter;
            self.initialization();
        end
        
        function ret = B(self, i, o)
            ret = self.b(i, o);
        end
        
        function initialization(self)
            n = self.N;
            m = self.M;
            
            self.A = ones(n,n)/n;
            for i = 1 : n
                sum = 0;
                for j = 1 : n
                    self.A(i, j) = self.A(i, j) + (-1)^(j) * 1 / ((rand(1)*100) + 100);
                    sum = sum + self.A(i,j);
                end
                
                if(sum > 1)
                    save = self.A(i,j);
                    self.A(i,j) = self.A(i,j) - (sum - 1);
                    sum = (sum - save) + self.A(i,j);
                elseif (sum < 1)
                    save = self.A(i,j);
                    self.A(i,j) = self.A(i,j) + (1 - sum);
                    sum = (sum - save) + self.A(i,j);
                end
            end
            
            self.b = ones(n, m)/m;
            for i = 1 : n
                sum = 0;
                for j = 1 : self.M
                    self.b(i, j) = self.b(i, j) + (-1)^(j) * 1 / ((rand(1) * 1000000) + 1000000);
                    sum = sum + self.b(i,j);
                end
                if(sum > 1)
                    save = self.b(i,j);
                    self.b(i,j) = self.b(i,j) - (sum - 1);
                    sum = (sum - save) + self.b(i,j);
                elseif (sum < 1)
                    save = self.b(i,j);
                    self.b(i,j) = self.b(i,j) + (1 - sum);
                    sum = (sum - save) + self.b(i,j);
                end
            end
            
            self.pi = ones(self.N,1)/self.N;
            
            self.Anum = zeros(self.N, self.N);
            self.Aden = zeros(self.N, 1);
            self.bnum = zeros(self.N, self.M);
            self.bden = zeros(self.N, 1);
            
            self.P = 1;
        end
        
        function [fw, c] = forward(self, O)
            T = length(O);
            fw = zeros(T, self.N);
            c = zeros(T,1);
            
            % compute fw(1, i)
            % 19
            c(1) = 0;
            for i = 1 : self.N
                fw(1, i) = self.pi(i) * self.B(i, O(1));
                if(self.scaling)
                    c(1) = c(1) + fw(1, i);
                end
            end
            
            % scale the fw(1, i)
            if(self.scaling)
                c(1) = 1 / c(1);
                for i = 1 : self.N
                    fw(1, i) = c(1) * fw(1, i);
                end
            end
            
            % compute fw(t, i)
            % 20!
            for t = 2 : T
                c(t) = 0;
                for j = 1 : self.N
                    fw(t, j) = 0;
                    for i = 1 : self.N
                        fw(t, j) = fw(t, j) + fw(t-1, i) * self.A(i, j);
                    end
                    fw(t, j) = fw(t, j)*self.B(j, O(t));
                    if(self.scaling)
                        c(t) = c(t) + fw(t, j);
                    end
                end
                
                if(self.scaling)
                    %scale fw(t, i)
                    c(t) = 1 / c(t);
                    for i = 1 : self.N
                        fw(t, i) = c(t) * fw(t, i);
                    end
                end
            end
        end
        
        function bw = backward(self, O, c)
            T  = length(O);
            bw = zeros(T, self.N);
            
            if(self.scaling)
                %Let bw(T, 1) = 1, scaled by c(T)
                for i = 1 : self.N
                    bw(T, i) = c(T);
                end
            else
                for i = 1 : self.N
                    bw(T, i) = 1;
                end
            end
            
            %25
            for t = T - 1 : -1 : 1
                for i = 1 : self.N
                    bw(t, i) = 0;
                    for j = 1 : self.N
                        bw(t, i) = bw(t, i) + self.A(i,j) * self.B(j, O(t+1)) * bw(t+1, j);
                    end
                    %scale bw(t,i) with same scale factor as fw(t,i)
                    if(self.scaling)
                        bw(t, i) = c(t) * bw(t, i);
                    end
                end
            end
        end
        
        function [gm, zet] = gamma(self, O, fw, bw)
            T = length(O);
            zet  = zeros(T, self.N, self.N);
            gm = zeros(T, self.N);
            
            %37
            for t = 1 : T - 1
                denom = 0;
                for i = 1 : self.N
                    for j = 1: self.N
                        denom = denom + fw(t, i) * self.A(i,j) * self.B(j, O(t+1)) * bw(t+1,j);
                    end
                end
                
                for i = 1 : self.N
                    zet(t, i) = 0;
                    for j = 1 : self.N
                        zet(t, i, j) = (fw(t, i) * self.A(i, j) * self.B(j, O(t+1)) * bw(t+1, j)) / denom;
                        gm(t,i) = gm(t,i) + zet(t, i, j);
                    end
                end
            end
            
            %Special case for zet(T, i)
            denom = 0;
            for i = 1 : self.N
                denom = denom + fw(T, i);
            end
            for i = 1 : self.N
                gm(T, i) = fw(T, i) / denom;
            end
        end
        
        function train_one(self, O)
            %1-Initialization
            iters = 0;
            oldLogProb = -Inf;
            T = length(O);
            
            %7-To interate or not to iterate...
            while(iters < self.maxIters)
                %2-The alpha-pass
                [fw, c] = self.forward(O);
                %3-The beta-pass
                bw = self.backward(O, c);
                %4-Compute zet(t, i, j) and gm(t,i)
                [gm, zet] = self.gamma(O, fw, bw);
                
                %5-Re-estimate A, B, pi
                
                %Re-estimate pi
                % 40a
                for i = 1 : self.N
                    self.pi(i) = gm(1, i);
                end
                
                %Re-estimate A
                % 40b
                for i = 1 : self.N
                    for j = 1 : self.N
                        numer = 0;
                        denom = 0;
                        for t = 1 : T - 1
                            numer = numer + zet(t, i, j);
                            denom = denom + gm(t, i);
                        end
                        self.A(i,j) = numer / denom;
                    end
                end
                
                %Re-estimate B
                % 40c
                for j = 1 : self.N
                    for k = 1 : self.M
                        numer = 0;
                        denom = 0;
                        for t = 1 : T
                            if O(t) == k
                                numer = numer + gm(t, j);
                            end
                            denom = denom + gm(t, j);
                        end
                        self.b(j, k) = numer / denom;
                    end
                end
                
                %6-compute log[P(O|model)]
                logProb = 0;
                if(self.scaling)
                    for i = 1 : T
                        logProb = logProb + log10(c(i));
                    end
                else
                    logProb = 0;
                    for i = 1 : self.N
                        logProb = logProb + fw(T, i);
                    end
                end
                logProb = -logProb;
                
                iters = iters + 1;
                if(logProb > oldLogProb)
                    oldLogProb = logProb;
                else
                    break;
                end
                
                fprintf('I');
                if mod(iters, 5) == 0
                    fprintf(' ');
                end
                
                if (mod(iters, 20) == 0) && iters ~= self.maxIters
                    fprintf(': %f\n', logProb);
                end
            end
            fprintf(' : %f\n', logProb);
            fprintf('Iterated %d times\n\n', iters);
        end
        
        function train_multiple(self, O)
            T = length(O);
            
            [fw, c] = self.forward(O);
            bw = self.backward(O, c);
            
            %102
            Pk = 1;
            for t = 1 : T - 1
                Pk = Pk * 1/c(t);
            end
            
            %109
            for i = 1 : self.N
                for j = 1 : self.N
                    num = 0;
                    den = 0;
                    for t = 1 : T - 1
                        num = num + fw(t,i) * self.A(i,j) * self.B(j, O(t+1)) * bw(t+1, j);
                        den = den + fw(t,i) * bw(t,i);
                    end
                    self.Anum(i,j) = self.Anum(i,j) + num / Pk;
                    self.Aden(i) = self.Aden(i) + den / Pk;
                end
            end
            
            %110
            for i = 1 : self.N
                for l = 1 : self.M
                    num = 0;
                    den = 0;
                    for t = 1 : T
                        if O(t) == l
                            num = num + fw(t, i) * bw(t, i);
                        end
                        den = den + fw(t, i) * bw(t, i);
                    end
                    self.bnum(i,l) = self.bnum(i,l) + num/Pk;
                    self.bden(i) = self.bden(i) + den/Pk;
                end
            end
        end
        
        function commit_mutiple(self)
            
            for i = 1 : self.N
                sum = 0;
                for j = 1 : self.N
                    %109
                    self.A(i,j) = self.Anum(i,j)/self.Aden(i);
                    sum = sum + self.A(i,j);
                end
                fprintf('Sum of A(%d,:) = %f\n', i, sum);
            end
            
            
            for i = 1 : self.N
                sum = 0;
                for l = 1 : self.M
                    %110
                    self.b(i,l) = self.bnum(i,l)/self.bden(i);
                    sum = sum + self.b(i,l);
                end
                fprintf('Sum of b(%d,:) = %f\n', i, sum);
            end
            
            self.Anum = zeros(self.N, self.N);
            self.Aden = zeros(self.N, 1);
            self.bnum = zeros(self.N, self.M);
            self.bden = zeros(self.N, 1);
        end
        
        function P = problem1(self, O)
            
            T = length(O);
            
            [~, c] = self.forward(O);
            %             P = 0;
            %             for i = 1 : self.N
            %                 P = P + fw(T, i);
            %             end
            P = 0;
            for t = 1 : T
                P = P + log10(c(t));
            end
            
            P=-P;
        end
        
        function printA(self, fileID)
            fprintf(fileID, '{');
            for i = 1 : self.N
                fprintf(fileID, '{');
                for j = 1 : self.N
                    fprintf(fileID, '%6.6f', self.A(i,j));
                    if j ~= self.N
                        fprintf(fileID, ', ');
                    end
                end
                
                if i == self.N
                    fprintf(fileID, '}');
                else
                    fprintf(fileID, '},\n');
                end
            end
            fprintf(fileID, '}');
        end
        
        function printB(self, fileID)
            fprintf(fileID, '{');
            for i = 1 : self.N
                fprintf(fileID, '{');
                for j = 1 : self.M
                    fprintf(fileID, '%6.6f', self.b(i,j));
                    if j ~= self.M
                        fprintf(fileID, ', ');
                    end
                end
                
                if i == self.N
                    fprintf(fileID, '}');
                else
                    fprintf(fileID, '},\n');
                end
            end
            fprintf(fileID, '}');
        end
        
        function printPi(self, fileID)
            fprintf(fileID, '{');
            for i = 1 : self.N
                fprintf(fileID, '%6.6f', self.pi(i));
                if i ~= self.N
                    fprintf(fileID, ', ');
                end
            end
            fprintf(fileID, '}');
        end
        
        function printCodeBook(self, fileID)
            S = length(self.codeData(1,:));
            fprintf(fileID, '{');
            for i = 1 : self.M
                fprintf(fileID, '{');
                for j = 1 : S
                    fprintf(fileID, '%+06.6f', self.codeData(i,j));
                    if j ~= S
                        fprintf(fileID, ', ');
                    end
                end
                if i == self.M
                    fprintf(fileID, '}');
                else
                    fprintf(fileID, '},\n');
                end
            end
            fprintf(fileID, '}');
        end
    end
    
end