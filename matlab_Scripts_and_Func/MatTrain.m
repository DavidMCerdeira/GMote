tic;
init

states = 8;

for j = 1 : number_of_gestures
    
    h{j} = HMM(gesture{j}, states, codebookSize);
    
    for i = 1 : number_of_samples
        seqx{i} = idx{j, i}';
    end
    
    [h{j}.A, h{j}.b] = hmmtrain(seqx, h{j}.A, h{j}.b);   
end

test
toc
