
vi_codebookSize = 2^4;

vi_gest1 = getDataFromFile('video', 1);
vi_gest2 = getDataFromFile('video', 2);
vi_gest3 = getDataFromFile('video', 3);
vi_gest4 = getDataFromFile('video', 4);
vi_gest5 = getDataFromFile('video', 5);
vi_gest6 = getDataFromFile('video', 6);
vi_gest7 = getDataFromFile('video', 7);


[vi_m, vi_p, vi_distor] = vqsplit([
                              vi_gest1;...

                              vi_gest2;...

                              vi_gest3;...

                              vi_gest4;...

                              vi_gest5;...

                              vi_gest6;...

                              vi_gest7;...
%{
                              vi_gest8;...

                              vi_gest9;...
                               %}
                             ]', vi_codebookSize);
                         
vi_md1 = KDTreeSearcher(vi_m');
                         
idx1 = knnsearch( vi_md1, sample{1,4});
idx2 = knnsearch( vi_md1, sample{2,4}); % match points with index
idx3 = knnsearch( vi_md1, sample{3,4});
idx4 = knnsearch( vi_md1, sample{4,4});
idx5 = knnsearch( vi_md1, sample{5,4});
idx6 = knnsearch( vi_md1, sample{6,4});
idx7 = knnsearch( vi_md1, sample{7,4});

h_matlab = HMM('video', 4, 2^4, vi_m', 0);

seqx = { idx2', idx3', idx4', idx5', idx6', idx7' };
%seqx
[TrainAx, TrainBx] = hmmtrain(seqx, h_matlab.A, h_matlab.b);


seq1 = hmmgenerate(160, h_matlab.A, h_matlab.b);
seq2 = hmmgenerate(168, h_matlab.A, h_matlab.b);
seq3 = hmmgenerate(140, h_matlab.A, h_matlab.b);
seq4 = hmmgenerate(123, h_matlab.A, h_matlab.b);
seq5 = hmmgenerate(170, h_matlab.A, h_matlab.b);
seq6 = hmmgenerate(125, h_matlab.A, h_matlab.b);

seqs = {seq1, seq2, seq3, seq4, seq5};
%seqs
[TrainAs, TrainBs] = hmmtrain(seqs, h_matlab.A, h_matlab.b);


%hmmdecode
