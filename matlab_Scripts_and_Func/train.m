init

iters = [100, 30, 100, 100, 100, 30, 30];

clear h
codebookSize = 2^4;
n_sates = 4;
count = 1;

% %{ 
for i = 1 : number_of_gestures
%for i = 2 : 3
    %vector quantization
    [m, ~, ~] = vqsplit([
        sample{i,1};
        
        sample{i,2};
        %{
        sample{i,3};
        
        sample{i,4};
        
        sample{i,5};
        
        sample{i,6};
        
        sample{i,7};
        
        sample{i,8};
        %}
        ]', codebookSize);

    h(i) = HMM(gesture{i}, n_sates, codebookSize, m', iters(i));
    idx = knnsearch( h(i).codebook, sample{i,1}); % match points with index
    fprintf('Training %s\n', gesture{i});
    h(i).train_one(idx);
end
fprintf('Done!\n');
%test