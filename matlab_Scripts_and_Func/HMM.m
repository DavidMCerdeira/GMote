classdef HMM < handle
    properties
        N     =  8; % number of states
        M     =  65535; % Observation vector size
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
        function B(self, i, O)
            
        end
        
        function initialization(self)
            n = self.N;
            m = self.M;
            self.A = ones(n,n)/n;
            self.b = ones(n, m)/m;
            self.pi = ones(n)/m;
        end
        
        function alpha(self, O)
            c = [];
            
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
            
            
        end
    end
end