init
states = 4;
%initate time counter
tic;
for j = 1 : number_of_gestures
    
    %create HMM models
    h{j} = HMM(gesture{j}, states, codebookSize);
    
    %load data sequences
    for i = 1 : number_of_samples
        seqx{i} = idx{j, i}';
    end
    
    %train the model
    [h{j}.A, h{j}.b] = hmmtrain(seqx, h{j}.A, h{j}.b);   
end

fprintf('Training took, %f seconds\n\n', toc);

test

