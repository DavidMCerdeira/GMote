%%{
gesture = 'circle';

cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote
%load training data
% for i = 1 : 10
%     aux = getDataFromFile(gesture, i);
%     gest(:,:,:,:,:,:,i) = aux;
% end

gest1 = getDataFromFile(gesture, 1);
gest2 = getDataFromFile(gesture, 2);
gest3 = getDataFromFile(gesture, 3);
gest4 = getDataFromFile(gesture, 4);
gest5 = getDataFromFile(gesture, 5);
gest6 = getDataFromFile(gesture, 6);
gest7 = getDataFromFile(gesture, 7);
gest8 = getDataFromFile(gesture, 8);
gest9 = getDataFromFile(gesture, 9);
gest10 = getDataFromFile(gesture, 10);


clear h;
codebookSize = 2^4;
h = HMM(gesture, 4, codebookSize);
count = 1;


%lp = fir1(50, 0.1);
%df = filter(lp, 1, dado);

[m, p, distor] = vqsplit([gest1;gest2;gest3;
                          gest4;gest5;gest6;]', codebookSize); %one training set
md1 = KDTreeSearcher(m'); % grow a kd-tree 
%}

%{
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


% idx = knnsearch(md1, dado1); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;

idx = knnsearch(md1, gest10); fprintf('Problem 1(should succeed): '); P = h.problem1(idx); fprintf('%f\n', P);

% df = filter(lp, 1, rand(192,6));
% idx = knnsearch(md1, df); % match points with index
% fprintf('Problem 1(should fail): ');
% P = h.problem1(idx);
% fprintf('%f\n', P);

% fprintf('Problem 1: ');
% P = h.problem1(gestD2(:,1));
% fprintf('%f\n', P);
%}

%%TESTING the vqsplit in two dimensions
%figure; plot(m(1,:), m(2,:), 'r*', dado(:,1), dado(:,2), 'g.')
%[m, p, distor] = vqsplit(dado(:,(1:2))', 2^5);


