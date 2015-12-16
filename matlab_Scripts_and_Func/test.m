clear h;
h = HMM('circle');
count = 1;

fprintf('Train %d:\n', count);
count = count + 1;
h.train(dadob(:,1));
fprintf('Train %d:\n', count);
h.train(test1(:,1));

% P = h.problem1(dado(:,1));
% fprintf('%d\n', P);

fprintf('Problem 1\n');
P = h.problem1(dadob(:,1));
fprintf('%d\n', P);


