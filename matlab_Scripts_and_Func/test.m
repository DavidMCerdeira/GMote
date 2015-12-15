clear h;
h = HMM('circle');
h.train(dado(:,1));

P = h.problem1(dado(:,1));
fprintf('%d\n', P);

P = h.problem1(test2(:,2));
fprintf('%d\n', P);