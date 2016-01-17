% This class was written based on two papers: 
% Lawrence R. Rabiner's "A Tutorial on Hidden Markov Models and Selected
% Appplications in Speech Recognition
% and
% Mark Stamp, of the Department of Computer Science in San Jose State
% University, "A Revealing Introduction to Hidden Markov Models"
classdef HMM < handle
    properties
        name  = 'undefined';
        %Main properties
        N     = []; % number of states
        M     = []; % number of features
        A     = []; % NxN transition probability matrix
        b     = []; % NxM mean vector (D = number of features)
        pi    = []; % Nx1 initial state distribution vector
        
        %functionality
        scaling = 1;
    end
    
    methods
        
        %Constructor: name of the model, number of states, number of
        %different emissions
        %input: name, number of states, number of different emission
        function self = HMM(name, numOfStates, codebookSize)
            self.name = name;
            self.N = numOfStates;
            self.M = codebookSize;
            self.initialization();
        end
        
        %this functions was implemented so that it could be reimplemented
        %using emission probability of observations instead of single
        %values
        function ret = B(self, i, o)
            ret = self.b(i, o);
        end
        
        %Initialize the model
        function initialization(self)
            n = self.N;
            m = self.M;
            
            %generate semi-random Transition matrix in order to resolve
            %problem 3 as suggest by Stamp
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
            
            %generate semi-random emission probability matrix in order to solve
            %problem 3 as suggest by Stamp
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
            
            %generate the initial state probabillity matrix as suggest by Stamp
            self.pi = ones(self.N,1)/self.N;           
        end
        
        %compute forward variable
        %Input: Obervation sequence
        %Output: fw: forward variable and the c: scale factors
        function [fw, c] = forward(self, O)
            %observation sequence's length
            T = length(O);
            %allocate space to forward variable
            fw = zeros(T, self.N);
            %initialize scale factors to 0
            c = zeros(T,1);
            
            %Using Stamp's alghorithm
            
            % compute fw(1, i)
            % 19 on Rabiner HMM paper
            c(1) = 0;
            for i = 1 : self.N
                fw(1, i) = self.pi(i) * (self.B(i, O(1)));
                if(self.scaling)
                    c(1) = c(1) + fw(1, i); %91 on Rabiner HMM paper
                end
            end
            
            % scale the fw(1, i)
            if(self.scaling)
                c(1) = 1 / c(1);
                for i = 1 : self.N
                    fw(1, i) = c(1) * (fw(1, i)); %93a on Rabiner HMM paper
                end
            end
            
            % compute fw(t, i)
            % 20 on Rabiner HMM paper
            for t = 2 : T
                c(t) = 0;
                for j = 1 : self.N
                    fw(t, j) = 0;
                    for i = 1 : self.N
                        fw(t, j) = fw(t, j) + fw(t-1, i) * (self.A(i, j));
                    end
                    fw(t, j) = (fw(t, j))*(self.B(j, O(t)));
                    if(self.scaling)
                        c(t) = c(t) + fw(t, j); %91 on Rabiner HMM paper
                    end
                end
                
                if(self.scaling)
                    %scale fw(t, i)
                    %93a on Rabiner HMM paper
                    c(t) = 1 / c(t);
                    for i = 1 : self.N
                        fw(t, i) = c(t) * (fw(t, i)); 
                    end
                end
            end
        end
        
        %compute backward variable
        %Input: O: Obervation sequence
        %Output: bw: backward variable
        function bw = backward(self, O, c)
            T  = length(O);
            bw = zeros(T, self.N);
            
            %Using Stamp's alghorithm
            
            if(self.scaling)
                %Let bw(T, 1) = 1, scaled by c(T)
                %94 on Rabiner HMM paper
                for i = 1 : self.N
                    bw(T, i) = c(T);
                end
            else
                for i = 1 : self.N
                    bw(T, i) = 1;
                end
            end
            
            %25 on Rabiner HMM paper
            for t = T - 1 : -1 : 1
                for i = 1 : self.N
                    bw(t, i) = 0;
                    for j = 1 : self.N
                        bw(t, i) = bw(t, i) + self.A(i,j) * self.B(j, O(t+1)) * bw(t+1, j);
                    end
                    %scale bw(t,i) with same scale factor as fw(t,i)
                    %94 on Rabiner HMM paper
                    if(self.scaling)
                        bw(t, i) = c(t) * bw(t, i);
                    end
                end
            end
        end
        
        %compute gamma, and zeta variable
        %Input: O: Obervation sequence, fw: forward variable,
        %bw: backward variable
        %Output: gm: gamma variable, zet: zeta variable
        function [gm, zet] = gamma(self, O, fw, bw)
            T = length(O);
            zet  = zeros(T, self.N, self.N);
            gm = zeros(T, self.N);
            
            %Using Stamp's alghorithm, changed variable names to match
            %Rabiner's
            
            %37 on Rabiner HMM paper
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
        
        %train the model with one single observation sequence
        %input: O: observation sequence, maxIters: maximum number of
        %iterations
        function train_one(self, O, maxIters)
            %1-Initialization
            iters = 0; % iteration counter
            oldLogProb = -Inf; % previous computed probability
            T = length(O); % observation sequence's length
            
            %Using Stamp's alghorithm on chapter 7, changed variable names to match
            %Rabiner's
            
            %7-To interate or not to iterate...
            while(iters < maxIters)
                %2-The alpha-pass
                [fw, c] = self.forward(O);
                %3-The beta-pass
                bw = self.backward(O, c);
                %4-Compute zet(t, i, j) and gm(t,i)
                [gm, zet] = self.gamma(O, fw, bw);
                
                %5-Re-estimate A, B, pi
                
                %Re-estimate pi
                % 40a on Rabiner HMM paper
                for i = 1 : self.N
                    self.pi(i) = gm(1, i);
                end
                
                %Re-estimate A
                % 40b on Rabiner HMM paper
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
                % 40c on Rabiner HMM paper
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
                
                %update probability
                iters = iters + 1;
                if(logProb > oldLogProb)
                    oldLogProb = logProb;
                else
                    break;
                end
                
                %print iterations so that the user can see some progress
                fprintf('I');
                if mod(iters, 5) == 0 && iters ~= maxIters
                    fprintf(' ');
                end
                
                if (mod(iters, 20) == 0) && iters ~= maxIters
                    fprintf(': %f\n', logProb);
                end
            end
            
            %final probability
            fprintf(' : %f\n', logProb);
            %number of iterations
            fprintf('Iterated %d times\n\n', iters);
        end
        
        %Solves Rabiner's problem 1: How likely it is that the observation
        %sequence belongs to a given HMM model
        %input: O: Observaion sequence
        %output: Probabilty of O belonging to the model
        function P = problem1(self, O)         
            T = length(O);            
            [~, c] = self.forward(O);
            P = 0;
            for t = 1 : T
                P = P + log10(c(t));
            end           
            P=-P;
        end
        
        %prints The model's Transitin matrix to a given file ID
        %input: file id
        %output: none
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
        
        %prints The model's transposed transitin matrix to a given file ID
        %input: file id
        %output: none
        function printAT(self, fileID)
            
            At = self.A';
            
            fprintf(fileID, '{');
            for i = 1 : self.N
                fprintf(fileID, '{');
                for j = 1 : self.N
                    fprintf(fileID, '%6.6f', At(i,j));
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
        
        %prints The model's emission probability matrix to a given file ID
        %input: file id
        %output: none
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
        
        %prints The model's transposed emission probability matrix to a given file ID
        %input: file id
        %output: none
        function printBT(self, fileID)
            bt = self.b';
            
            fprintf(fileID, '{');
            for i = 1 : self.M
                fprintf(fileID, '{');
                for j = 1 : self.N
                    fprintf(fileID, '%6.6f', bt(i,j));
                    if j ~= self.N
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
        
        %prints the model's initial state probability to a given file ID
        %input: file id
        %output: none
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
    end
    
end