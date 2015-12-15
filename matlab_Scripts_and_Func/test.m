clear h;
h = HMM('circle');
h.train(dado(:,1));

P = h.problem1(dado(:,1));