init

iters = repmat(75, number_of_gestures);

clear h
h = cell(number_of_gestures);
%{
codebookSize = 2^4;
n_sates = 3;
count = 1;

for i = 1 : number_of_gestures
    %vector quantization
    [m, ~, ~] = vqsplit([
        sample{i,1};
        
        sample{i,2};
        
        sample{i,3};
%{
        sample{i,4};
        
        sample{i,5};
        
        sample{i,6};
%}
        sample{i,7};
        
        sample{i,8};
       
        ]', codebookSize);

    h{i} = HMM(gesture{i}, n_sates, codebookSize, m', iters(i));
    idx = knnsearch( h{i}.codebook, sample{i,4}); % match points with index
    fprintf('Training %s\n', gesture{i});
    h{i}.train_one(idx);
end
%}

% %{
codebookSize = 2^1;
n_sates = 2;
count = 1;
iter = 1;

fprintf('Multiple:\n');
for i = 1 : number_of_gestures
    fprintf('Training %s\n', gesture{i});
    %vector quantization
    [m, ~, ~] = vqsplit([sample{i,1}; sample{i,2}; sample{i,3}; sample{i,4}; sample{i,5}; sample{i,6};  sample{i,7};  sample{i,8};]', codebookSize);
    h{i} = HMM(gesture{i}, n_sates, codebookSize, m', iters(i));
    
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