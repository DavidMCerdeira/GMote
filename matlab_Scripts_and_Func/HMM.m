classdef HMM < handle
    properties
        name  = 'undefined';
        %Main properties
        N     = 8;  % number of states
        M     = 255; % number of features
        A     = []; % NxN transition probability matrix
        b     = []; % NxM mean vector (D = number of features)
        pi    = []; % Nx1 initial state distribution vector
        
        %aproximate
        ADen     = [];
        ANum     = [];
        bDen     = [];
        bNum     = [];
        
        maxIters = 200;
        
        %functionality
        scaling = 1;
        
    end
    
    methods
        function self = HMM(name, numOfStates, codebookSize)
            self.name = char(name);
            self.N = numOfStates;
            self.M = codebookSize;
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
                    self.A(i, j) = self.A(i, j) + (-1)^(rand(1)*2-1) * 1 / ((rand(1)*100) + 100);
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
                    self.b(i, j) = self.b(i, j) + (-1)^(rand(1)*2-1) * 1 / ((rand(1) * 1000000) + 1000000);
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
            
            self.ADen = zeros(self.N, self.N);
            self.ANum = zeros(self.N, self.N);
            
            self.bDen = zeros(self.N, self.M);
            self.bNum = zeros(self.N, self.M);
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
                
                fprintf('LogProb = %f\n', logProb);
                
                iters = iters + 1;
                if(logProb > oldLogProb)
                    oldLogProb = logProb;
                else
                    break;
                end
            end
            
            fprintf('Iterated %d times\n', iters);
        end
        
        function train_multiple(self, O)
            T = length(O);
            [fw, c] = self.forward(O);
            bw = self.backward(O, c);
            
            %102
            P = 1;
            for t = 1 : T - 1
                P = P * 1/c(t);
            end
            
            num = zeros(self.N, self.N);
            den = zeros(self.N, self.N);
            
            %109 % but already scaled
            for i = 1 : self.N
                for j = 1 : self.N
                    for t = 1 : 1
                        num(i,j) = num(i,j) + fw(t,i) * self.A(i,j) * self.B(j, O(t+1)) * bw(t+1, j);
                        den(i,j) = den(i,j) + fw(t,i) * bw(t,i); %! vai somar N vezes! sem ser necessário
                    end
                    
                    self.ANum(i,j) = self.ANum(i,j) + num(i,j) / P;
                    self.ADen(i,j) = self.ADen(i,j) + den(i,j) / P;
                end
            end
            
            %110
            for i = 1 : self.N
                for l = 1 : self.M
                    for t = 1 : T
                        if O(t) == l
                            self.bNum(i,l) = self.bNum(i,l) + fw(t, i) * bw(t, i);
                        end
                        self.bDen(i,l) = self.bDen(i,l) + fw(t, i) * bw(t, i);
                    end
                    
                    self.bNum(i,l) = self.bNum(i,l) / P;
                    self.bDen(i,l) = self.bDen(i,l) / P;                   
                end
            end
        end
        
        function commit_mutiple(self)
            
            for i = 1 : self.N
                sum = 0;
                for j = 1 : self.N
                    %109
                    self.A(i,j) = self.ANum(i,j)/self.ADen(i,j);
                    sum = sum + self.A(i,j);
                end
                fprintf('Sum of A(i,:) = %f\n', sum);
            end
            
           
            for i = 1 : self.N
                sum = 0;
                for l = 1 : self.M
                    %110
                    self.b(i,l) = self.bNum(i,l)/self.bDen(i,l);
                    sum = sum + self.b(i,l);
                end
                fprintf('Sum of b(i,:) = %f\n', sum);
            end
            
            self.ADen = zeros(self.N, self.N);
            self.ANum = zeros(self.N, self.N);
            
            self.bDen = zeros(self.N, self.M);
            self.bNum = zeros(self.N, self.M);
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
    end
end