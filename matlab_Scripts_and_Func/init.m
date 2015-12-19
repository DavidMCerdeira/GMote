% % {
gesture = 'video';

cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote

gest1 = getDataFromFile(gesture, 1);
gest2 = getDataFromFile(gesture, 2);
gest3 = getDataFromFile(gesture, 3);
gest4 = getDataFromFile(gesture, 4);
gest5 = getDataFromFile(gesture, 5);
gest6 = getDataFromFile(gesture, 6);
gest7 = getDataFromFile(gesture, 7);
gest8 = getDataFromFile(gesture, 8);
gest9 = getDataFromFile(gesture, 9);
%gest10 = getDataFromFile(gesture, 10);

clear h;
codebookSize = 2^4;
h = HMM(gesture, 4, codebookSize);
count = 1;

[m, p, distor] = vqsplit([gest1]', codebookSize); %one training set
md1 = KDTreeSearcher(m'); % grow a kd-tree 

%training
idx = knnsearch(md1, gest1); % match points with index
fprintf('Train %d:\n', count);
h.train(idx);
count = count + 1;
% idx = knnsearch(md1, gest2); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
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

%}