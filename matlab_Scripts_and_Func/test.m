clear h;
h = HMM('circle', 3);
count = 1;

h.train(circleD3(:,1));
fprintf('Train %d:\n', count);
count = count + 1;

fprintf('Train %d:\n', count);
count = count + 1;
h.train(circleD1(:,1));
% fprintf('Train %d:\n', count);
% count = count + 1;

% h.train(circleD3(:,1));

fprintf('Problem 1: ');
P = h.problem1(circleD3(:,1));
fprintf('%f\n', P);

% fprintf('Problem 1: ');
% P = h.problem1(circleD2(:,1));
% fprintf('%f\n', P);


