clear h;
codebookSize = 2^4;
h = HMM(gesture, 4, codebookSize);
count = 1;

[m, p, distor] = vqsplit(gest1', codebookSize); %one training set
md1 = KDTreeSearcher(m'); % grow a kd-tree 

%training
idx = knnsearch(md1, gest1); % match points with index
figure
plot(gest1);
title('Training');

fprintf('Train %d:\n', count);
h.train(idx);
count = count + 1;
idx = knnsearch(md1, gest2); % match points with index
fprintf('Train %d:\n', count);
h.train(idx);
% count = count + 1;
% idx = knnsearch(md1, gest3); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;
% idx = knnsearch(md1, gest4); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;
% idx = knnsearch(md1, gest5); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;idx = knnsearch(md1, gest6); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;
