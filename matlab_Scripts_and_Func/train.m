%init

iters = repmat(1, number_of_gestures);

clear h
h = cell(number_of_gestures, 1);
%%{
n_sates = 8;

for i = 1 : number_of_gestures
    h{i} = HMM(gesture{i}, n_sates, codebookSize);
    idx = knnsearch(codebook, sample{i,2}); % match points with index
    fprintf('Training %s\n', gesture{i});
    h{i}.train_one(idx, iters(i));
end
%}

%{
codebookSize = 2^2;
n_sates = 2;
count = 1;
iter = 1;

fprintf('Multiple:\n');
for i = 1 : number_of_gestures
    fprintf('Training %s\n', gesture{i});
    %vector quantization
    [m, ~, ~] = vqsplit([sample{i,1}; sample{i,2}; sample{i,3}; sample{i,4}; sample{i,5}; sample{i,6};  sample{i,7};  sample{i,8};]', codebookSize);
    h{i} = HMM(gesture{i}, n_sates, codebookSize, m', 0);
    
    for it = 1 : iter       
        for j = 1 : 5
            idx = knnsearch( h{i}.codebook, sample{i,j}); % match points with index
            h{i}.train_multiple(idx);
        end
        h{i}.commit_multiple
        fprintf('I');
    end
    
    fprintf('\n');
end
%}

test