classdef HMM < handle
    properties
        N     =  8; % number of states
        M     =  65535; % Observation vector number of possible different values
        A     = []; % NxN transition probability matrix
        pi    = []; % Nx1 initial state distribution vector
        b     = []; % DxN mean vector (D = number of features)
        %Sigma = []; % DxDxN covariance matrix
        %name  = '';
        
        fw   = [];
        bw   = [];
        
        MaxIters = 100;
    end
    
    methods
        function B(self, i, o)
            
        end
        
        function initialization(self)
            n = self.N;
            m = self.M;
            self.A = ones(n,n)/n;
            self.b = ones(n, m)/m;
            self.pi = ones(n)/m;
        end
        
        function problem3(self, O)
            iters = 0;
            oldLogProb = -Inf;
            T = length(O);
            
            %7-To interate or not to iterate...
            while(iters < maxIters)
                
                c = zeros(lentgh(O));
                %2-The alpha-pass
                % compute fw(1, i)
                c(1) = 0;
                for i = 1 : self.N
                    self.fw(1, i) = self.pi(i) * self.B(self, i, O(0));
                    c(1) = c(1) + self.fw(1, i);
                end
                
                % scale the fw(1, i)
                c(1) = 1 / c(1);
                for i = 1 : self.N
                    self.fw(1, i) = c(1)*self.fw(1, i);
                end
                
                %compute fw(t, i)
                for t = 2 : T
                    c(t) = 0;
                    for i = 1 : self.N
                        self.fw(t, i) = 0;
                        for j = 1 : self.N
                            self.fw(t, i) = self.fw(t, i) + self.fw(t-1, j) * self.A(j, i);
                        end
                        self.fw(t, i) = self.fw(t, 1)*self.B(i, O(t));
                        c(t) = c(t) + self.fw(t, i);
                    end
                    
                    %scale fw(t, i)
                    c(t) = 1 / c(t);
                    for i = 1 : self.N
                        self.fw(t, i) = c(t) * self.fw(t, i);
                    end
                end
                
                
                %3-The beta-pass
                %Let bw(T, 1) = 1, scaled by c(T)
                for i = 1 : self.N
                    self.bw(T, i) = c(T);
                end
                
                for t = T - 1 : -1 : 1
                    for i = 1 : self.N
                        self.bw(t, i) = 0;
                        for j = 0 : self.N
                            self.bw(t, i) = self.bw(t, i) + self.A(i,j)*B(j, O(t+1))*self.bw(t+1, j);
                        end
                        self.bw(t, i) = c(t) * self.bw(t, i);
                    end
                end
                
                %4-Compute gamma(t, i, j) and gamma(t,i)
                gm = zeros(T, self.N);
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
                            gm(t,i) = gm(t,i) + gm(t, i, j);
                        end
                    end
                end
                
                %Special case for gm(T, i)
                denom = 0;
                for i = 1 : self.N
                    denom = denom + self.fw(T, i);
                end
                for i = 0 : self.N
                    gm(T, i) = self.fw(T, i) / denom;
                end
                
                %5-Re-estimate A, B, pi
                for i = 1 : self.N
                    self.pi(i) = gm(1, i);
                end
                
                %Re-estimate A
                for i = 1 :self.N
                    for j = 1 : self.N
                        numer = 0;
                        denom = 0;
                        for t = 1 : T -1
                            numer = numer + gm(t, i, j);
                            denom = denom + gm(t, i);
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
    end
end