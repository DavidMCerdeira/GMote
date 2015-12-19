gesture = 'circle';

cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote
%load training data
% for i = 1 : 10
%     aux = getDataFromFile(gesture, i);
%     gest(:,:,:,:,:,:,i) = aux;
% end

circle1 = getDataFromFile(gesture, 1);
circle2 = getDataFromFile(gesture, 2);
circle3 = getDataFromFile(gesture, 3);
circle4 = getDataFromFile(gesture, 4);
circle5 = getDataFromFile(gesture, 5);
circle6 = getDataFromFile(gesture, 6);
circle7 = getDataFromFile(gesture, 7);
circle8 = getDataFromFile(gesture, 8);
circle9 = getDataFromFile(gesture, 9);
circle10 = getDataFromFile(gesture, 10);


clear h;
codebookSize = 2^4;
h = HMM(gesture, 4, codebookSize);
count = 1;

%lp = fir1(50, 0.1);
%df = filter(lp, 1, dado);

[m, p, distor] = vqsplit([circle1;circle2;circle3;
                          circle4;circle5;circle6;]', codebookSize); %one training set
md1 = KDTreeSearcher(m'); % grow a kd-tree 

idx = knnsearch(md1, circle1); % match points with index
fprintf('Train %d:\n', count);
h.train(idx);
count = count + 1;
% idx = knnsearch(md1, circle2); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;
% idx = knnsearch(md1, circle3); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;
% idx = knnsearch(md1, circle4); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;
% idx = knnsearch(md1, circle5); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;idx = knnsearch(md1, circle6); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;


% idx = knnsearch(md1, dado1); % match points with index
% fprintf('Train %d:\n', count);
% h.train(idx);
% count = count + 1;

idx = knnsearch(md1, circle10); fprintf('Problem 1(should succeed): '); P = h.problem1(idx); fprintf('%f\n', P);

% df = filter(lp, 1, rand(192,6));
% idx = knnsearch(md1, df); % match points with index
% fprintf('Problem 1(should fail): ');
% P = h.problem1(idx);
% fprintf('%f\n', P);

% fprintf('Problem 1: ');
% P = h.problem1(circleD2(:,1));
% fprintf('%f\n', P);


%%TESTING the vqsplit in two dimensions
%figure; plot(m(1,:), m(2,:), 'r*', dado(:,1), dado(:,2), 'g.')
%[m, p, distor] = vqsplit(dado(:,(1:2))', 2^5);


