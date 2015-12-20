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
        %multiple sample counter
        mCount = 0;
        
        maxIters = 200;
        
        %functionality
        scaling = 1;
        
        % Auxialiry
        fw    = []; % DxN
        bw    = []; % DxN
        zet    = [];
        gm   = [];
        c     = []; % scale factor
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
                    self.A(i, j) = self.A(i, j) + (-1)^j * 1 / ((rand(1)*100) + 100);
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
                    self.b(i, j) = self.b(i, j) + (-1)^j * 1 / ((rand(1) * 1000000) + 1000000);
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
        
        function forward(self, O)
            T = length(O);
            
            % compute fw(1, i)
            % 19
            self.c(1) = 0;
            for i = 1 : self.N
                self.fw(1, i) = self.pi(i) * self.B(i, O(1));
                if(self.scaling)
                    self.c(1) = self.c(1) + self.fw(1, i);
                end
            end
            
            % scale the fw(1, i)
            if(self.scaling)
                self.c(1) = 1 / self.c(1);
                for i = 1 : self.N
                    self.fw(1, i) = self.c(1) * self.fw(1, i);
                end
            end
            
            % compute fw(t, i)
            % 20!
            for t = 2 : T
                self.c(t) = 0;
                for j = 1 : self.N
                    self.fw(t, j) = 0;
                    for i = 1 : self.N
                        self.fw(t, j) = self.fw(t, j) + self.fw(t-1, i) * self.A(i, j);
                    end
                    self.fw(t, j) = self.fw(t, j)*self.B(j, O(t));
                    if(self.scaling)
                        self.c(t) = self.c(t) + self.fw(t, j);
                    end
                end
                
                if(self.scaling)
                    %scale fw(t, i)
                    self.c(t) = 1 / self.c(t);
                    for i = 1 : self.N
                        self.fw(t, i) = self.c(t) * self.fw(t, i);
                    end
                end
            end
        end
        
        function backward(self, O)
            T  = length(O);
            if(self.scaling)
                %Let bw(T, 1) = 1, scaled by c(T)
                for i = 1 : self.N
                    self.bw(T, i) = self.c(T);
                end
            else
                for i = 1 : self.N
                    self.bw(T, i) = 1;
                end
            end
            
            %25
            for t = T - 1 : -1 : 1
                for i = 1 : self.N
                    self.bw(t, i) = 0;
                    for j = 1 : self.N
                        self.bw(t, i) = self.bw(t, i) + self.A(i,j) * self.B(j, O(t+1)) * self.bw(t+1, j);
                    end
                    %scale bw(t,i) with same scale factor as fw(t,i)
                    if(self.scaling)
                        self.bw(t, i) = self.c(t) * self.bw(t, i);
                    end
                end
            end
        end
        
        function gamma(self, O)
            T = length(O);
            self.zet  = zeros(T, self.N, self.N);
            self.gm = zeros(T, self.N);
            
            %37
            for t = 1 : T - 1
                denom = 0;
                for i = 1 : self.N
                    for j = 1: self.N
                        denom = denom + self.fw(t, i) * self.A(i,j) * self.B(j, O(t+1)) * self.bw(t+1,j);
                    end
                end
                
                for i = 1 : self.N
                    self.zet(t, i) = 0;
                    for j = 1 : self.N
                        self.zet(t, i, j) = (self.fw(t, i) * self.A(i, j) * self.B(j, O(t+1)) * self.bw(t+1, j)) / denom;
                        self.gm(t,i) = self.gm(t,i) + self.zet(t, i, j);
                    end
                end
            end
            
            %Special case for zet(T, i)
            denom = 0;
            for i = 1 : self.N
                denom = denom + self.fw(T, i);
            end
            for i = 1 : self.N
                self.gm(T, i) = self.fw(T, i) / denom;
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
                self.forward(O);
                %3-The beta-pass
                self.backward(O);
                %4-Compute zet(t, i, j) and gm(t,i)
                self.gamma(O)
                
                %5-Re-estimate A, B, pi
                
                %Re-estimate pi
                % 40a
                for i = 1 : self.N
                    self.pi(i) = self.gm(1, i);
                end
                
                %Re-estimate A
                % 40b
                for i = 1 : self.N
                    for j = 1 : self.N
                        numer = 0;
                        denom = 0;
                        for t = 1 : T - 1
                            numer = numer + self.zet(t, i, j);
                            denom = denom + self.gm(t, i);
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
                                numer = numer + self.gm(t, j);
                            end
                            denom = denom + self.gm(t, j);
                        end
                        self.b(j, k) = numer / denom;
                    end
                end
                
                %6-compute log[P(O|model)]
                logProb = 0;
                if(self.scaling)
                    for i = 1 : T
                        logProb = logProb + log10(self.c(i));
                    end
                else
                    logProb = 0;
                    for i = 1 : self.N
                        logProb = logProb + self.fw(T, i);
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
            
            self.forward(O);
            self.backward(O);
            
            %102
            P = 1;
            for t = 1 : length(O)
                P = P * 1/self.c(t);
            end
            
            %109 % but already scaled
            for i = 1 : self.N
                for j = 1 : self.N
                    for t = 1 : length(O)-1
                        self.ANum(i,j) = self.ANum(i,j) + self.fw(t,i) * self.A(i,j) * self.B(j, O(t+1)) * self.bw(t+1, j);
                        self.ADen(i,j) = self.ADen(i,j) + self.fw(t,i) * self.bw(t,i);
                    end
                    
                    self.ANum(i,j) = self.ANum(i,j) / P;
                    self.ADen(i,j) = self.ADen(i,j) / P;
                end
            end
            
            %110
            for i = 1 : self.N
                for l = 1 : self.M
                    for t = 1 : length(O)
                        if O(t) == l
                            self.bNum(i,l) = self.bNum(i,l) + self.fw(t, i) * self.bw(t, i);
                        else
                            self.bNum(i,l) = self.bNum(i,l) + 0;
                        end
                        
                        self.bDen(i,l) = self.bDen(i,l) + self.fw(t, i) * self.bw(t, i);
                    end
                    
                    self.bNum(i,l) = self.bNum(i,l) / P;
                    self.bDen(i,l) = self.bDen(i,l) / P;                   
                end
            end
        end
        
        function commit_mutiple(self)           
            for i = 1 : self.N
                for j = 1 : self.N
                    %109
                    self.A(i,j) = self.ANum(i,j)/self.ADen(i,j);
                end
            end
            
            for i = 1 : self.N
                for l = 1 : self.M
                    %110
                    self.b(i,l) = self.bNum(i,l)/self.bDen(i,l);
                    
                end
            end
            
            self.ADen = zeros(self.N, self.N);
            self.ANum = zeros(self.N, self.N);
            
            self.bDen = zeros(self.N, self.M);
            self.bNum = zeros(self.N, self.M);
        end
        
        function P = problem1(self, O)
            
            T = length(O);
            
            self.forward(O);
            %             P = 0;
            %             for i = 1 : self.N
            %                 P = P + self.fw(T, i);
            %             end
            P = 0;
            for t = 1 : T
                P = P + log10(self.c(t));
            end
            
            P=-P;
        end
    end
end