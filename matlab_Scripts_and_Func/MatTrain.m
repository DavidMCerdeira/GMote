h_matlab = HMM('video', 4, codebookSize);

GestID = 2;

for i = 1 : number_of_samples
    seqx{i} = idx{GestID, i}';
end
[TrainAx, TrainBx] = hmmtrain(seqx, h_matlab.A, h_matlab.b);
