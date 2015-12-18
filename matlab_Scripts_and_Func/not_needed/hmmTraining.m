% Create a HMM model
% SP - start probability
% A - transition matrix
% B - Emission
%
% Note: for each state s in S and t in T
% the items should follow the condition
% sum  SP(s) = 1
% sum  A(s1, s2) = 1
% sum  B(s, t) = 1

N = 8;
M = 40;

dbq = dn + 65534/2;
dbq = round(dbq/(65534/M));

[vec, n] = getFrames(dbq(:,1), 0, 9);

Aguess = ones(N)/N;
Bguess = ones(N,M)/M;

[A, B] = hmmtrain(vec, Aguess, Bguess);

OS=myViterbi(vec, (1:N), A, B, ones(N,1)/N);
%OS = hmmviterbi(vec, A, B);