classdef HMM < handle
    properties
        name  = 'undefined';
        %Main properties
        N     =  8; % number of states
        M     =  65535; % number of features
        A     = []; % NxN transition probability matrix
        pi    = []; % Nx1 initial state distribution vector
        b     = []; % MxN mean vector (D = number of features)
        MaxIters = 100;
        
        % Auxialiry
        fw    = []; % DxN
        bw    = []; % DxN
        c     = []; % scale factor            
    end
    
    methods        
        function self = HMM(name)
            self.name = char(name);
        end
        
        function ret = B(self, i, o)
            ret = self.b(i, o);
        end
        
        function initialization(self)
            n = self.N;
            m = self.M;
            self.A = ones(n,n)/n;
            self.b = ones(n, m)/m;
            self.pi = ones(n)/m;
        end
        
        function forward(self, O)
            
            % compute fw(1, i)
            self.c(1) = 0;
            for i = 1 : self.N
                self.fw(1, i) = self.pi(i) * self.B(self, i, O(0));
                self.c(1) = self.c(1) + self.fw(1, i);
            end
            
            % scale the fw(1, i)
            self.c(1) = 1 / self.c(1);
            for i = 1 : self.N
                self.fw(1, i) = self.c(1)*self.fw(1, i);
            end
            
            %compute fw(t, i)
            for t = 2 : T
                self.c(t) = 0;
                for i = 1 : self.N
                    self.fw(t, i) = 0;
                    for j = 1 : self.N
                        self.fw(t, i) = self.fw(t, i) + self.fw(t-1, j) * self.A(j, i);
                    end
                    self.fw(t, i) = self.fw(t, 1)*self.B(i, O(t));
                    self.c(t) = self.c(t) + self.fw(t, i);
                end
                
                %scale fw(t, i)
                self.c(t) = 1 / self.c(t);
                for i = 1 : self.N
                    self.fw(t, i) = self.c(t) * self.fw(t, i);
                end
            end
        end
        
        function backward(self, O)
            %Let bw(T, 1) = 1, scaled by c(T)
            for i = 1 : self.N
                self.bw(T, i) = self.c(T);
            end
            
            for t = T - 1 : -1 : 1
                for i = 1 : self.N
                    self.bw(t, i) = 0;
                    for j = 0 : self.N
                        self.bw(t, i) = self.bw(t, i) + self.A(i,j)*B(j, O(t+1))*self.bw(t+1, j);
                    end
                    self.bw(t, i) = self.c(t) * self.bw(t, i);
                end
            end
        end
        
        function train(self, O)
            %1-Initialization
            iters = 0;
            oldLogProb = -Inf;
            T = length(O);
            
            %7-To interate or not to iterate...
            while(iters < maxIters)
                %2-The alpha-pass
                self.forward(O);
                %3-The beta-pass
                self.backward(O);
                
                %4-Compute gamma(t, i, j) and gamma(t,i)
                gm  = zeros(T, self.N, self.N);
                gms = zeros(T, self.N);
                for t = 1 : T - 1
                    denom = 0;
                    for i = 1 : self.N
                        for j = 1: self.N
                            denom = denom + self.fw(t, i) * self.A(i,j) * B(j, O(t+1)) * self.bw(t+1,j);
                        end
                    end
                    
                    for i = 1 : self.N
                        gm(t, j) = 0;
                        for j = 0 : self.N
                            gm(t, i, j) = (self.fw(t, i) * self.A(i, j) * B(j, O(t+1))) / denom;
                            gms(t,i) = gms(t,i) + gm(t, i, j);
                        end
                    end
                end
                
                %Special case for gm(T, i)
                denom = 0;
                for i = 1 : self.N
                    denom = denom + self.fw(T, i);
                end
                for i = 0 : self.N
                    gms(T, i) = self.fw(T, i) / denom;
                end
                
                %5-Re-estimate A, B, pi
                
                %Re-estimate pi
                for i = 1 : self.N
                    self.pi(i) = gms(1, i);
                end
                
                %Re-estimate A
                for i = 1 :self.N
                    for j = 1 : self.N
                        numer = 0;
                        denom = 0;
                        for t = 1 : T -1
                            numer = numer + gm(t, i, j);
                            denom = denom + gms(t, i);
                        end
                        self.A(i,j) = numer / denom;
                    end
                end
                
                %Re-estimate B
                for i = 1 : self.N
                    for j = 1 : self.M
                        numer = 0;
                        denom = 0;
                        for t = 1 : T
                            if O(t) == j
                                numer = numer + gm(t, i);
                            end
                            denom = denom + gm(t, i);
                        end
                    end
                    self.b(i, j) = numer / denom;
                end
                
                %6-compute log[P(O|model)]
                logProb = 0;
                for i = 1 : T
                    logProb = logProb + log10(c(i), 10);
                end
                
                
                iters = iters + 1;
                
                if(logProb > oldLogProb)
                    break;
                else
                    oldLogProb = logProb;
                end
            end
        end
        
        function P = problem1(self, O)           
            P = 0;
            T = length(O);
            
            self.forward(O);                                   
            for i = 1 : self.N
                P = P + self.fw(T, i);
            end
        end
    end
end