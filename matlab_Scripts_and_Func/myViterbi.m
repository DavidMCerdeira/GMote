% use viterbi to decode a series of observations to the most likely
% series of states
%
% T: array of observations, length `t`
% S: array of states, length `m` (start and end states omitted for clarity)
% V: observations, length `n`
% A(m, m): state transition probability distribution
% B(m, n): observation probability distribution

%https://gist.github.com/aaronj1335/9650261
function [OS] = myViterbi(T, S, A, B)
  
    t = lenght(T);
    m = length(S);

    V = zeros(t, m);

    % store back-references to figure out the actual path taken to get there
    P = zeros(t, m); 
    
    % get array of  probabilities of having been in each previous step,
    X = zeros(m);

    %SP Start probability = pi(s)
    SP = zeros(m);
    for s = 1 : m
        V(0, s) = SP(s) * B(s, T(0));
        P(0, s) = 0;
    end
    
    % iterate through each time step
    for i = 2 : t
        % and consider each state
        for s = 1 : m
           % multiplied by the probability of transitioning to the current state
            for x = 1 : m
                X(x) = V(i-1, x) * A(x, s);
            end
            V(i, s) = max(X) * B(s, T(i));
            P(i, s) = argmax(X);
        end
    end

    % build the output sequence by tracing the backpointers of the highest
    % probabilities at each step
    OS = zeros(t);
    OS(t) = P(t, argmax(V(t)));
    for i = t-1 : 1
        prepend(OS, P(i, argmax(V(i))))
    end
end

% use viterbi to calculate observation probability
%
% T: array of observations, length `t`
% S: array of states, length `m` (start and end states omitted for clarity)
% V: observations, length `n`
% A(m, m): state transition probability distribution
% B(m, n): observation probability distribution
% function viterbi_obs(T, S, A, B)
%   V = zeros(t, m)
% 
%   % iterate through each time step
%   for i in 1:t
%     % and consider each state
%     for s in 1:m
% 
%       % calculate the sum of the probabilities of having been in every
%       % state before, times the state-transition probability
%       for o in 1:m
%         V(i, s) += V(i-1, o) * A(o, s)
%       end
% 
%       % finally multiply that by the probability of seeing the current
%       % observation given this state
%       V(i, s) *= B(s, T(i))
%     end
%   end
% 
%   return sum(V(t))
% end