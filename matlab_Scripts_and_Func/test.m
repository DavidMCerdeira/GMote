clear h;
codebookSize = 2^4;
h = HMM('circle', 8, codebookSize);
count = 1;

lp = fir1(50, 0.1);
df = filter(lp, 1, dado);

[m, p, distor] = vqsplit(df', codebookSize); %one training set
md1 = KDTreeSearcher(m'); % grow a kd-tree 

idx = knnsearch(md1, df); % match points with index
fprintf('Train %d:\n', count);
h.train(idx);
count = count + 1;

% idx = knnsearch(md1, dado1); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;

df = filter(lp, 1, dado2);
idx = knnsearch(md1, df); % match points with index
fprintf('Problem 1(should succeed): ');
P = h.problem1(idx);
fprintf('%f\n', P);

df = filter(lp, 1, rand(192,6));
idx = knnsearch(md1, df); % match points with index
fprintf('Problem 1(should fail): ');
P = h.problem1(idx);
fprintf('%f\n', P);

% fprintf('Problem 1: ');
% P = h.problem1(circleD2(:,1));
% fprintf('%f\n', P);


%%TESTING the vqsplit in two dimensions
%figure; plot(m(1,:), m(2,:), 'r*', dado(:,1), dado(:,2), 'g.')
%[m, p, distor] = vqsplit(dado(:,(1:2))', 2^5);


