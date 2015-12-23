%init

iters = repmat(1, number_of_gestures);

clear h
<<<<<<< HEAD
h = cell(number_of_gestures);

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
    %idx = knnsearch( h{i}.codebook, sample{i,4}); % match points with index
    fprintf('Training %s\n', gesture{i});
    %h{i}.train_one(idx);
=======
h = cell(number_of_gestures, 1);
%%{
n_sates = 8;

for i = 1 : number_of_gestures
    h{i} = HMM(gesture{i}, n_sates, codebookSize);
    idx = knnsearch(codebook, sample{i,2}); % match points with index
    fprintf('Training %s\n', gesture{i});
    h{i}.train_one(idx, iters(i));
>>>>>>> b0c0a4d570d58bc8d4bee86589943a745f2b1ba9
end
%{%}

%{
<<<<<<< HEAD
codebookSize = 2^1;
=======
codebookSize = 2^2;
>>>>>>> b0c0a4d570d58bc8d4bee86589943a745f2b1ba9
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

h_matlab = HMM('circle', 4, 2^4, m', 0);

init

 idx2 = knnsearch( h{2}.codebook, sample{2,4}); % match points with index
 idx3 = knnsearch( h{3}.codebook, sample{3,4});
 idx4 = knnsearch( h{4}.codebook, sample{4,4});
 idx5 = knnsearch( h{5}.codebook, sample{5,4});
 idx6 = knnsearch( h{6}.codebook, sample{6,4});
 idx7 = knnsearch( h{7}.codebook, sample{7,4});

 seq ={ idx2; idx3; idx4; idx5; idx6; idx7}; 
 
[TrainA, TrainB] = hmmtrain(seq, h_matlab.A, h_matlab.b); 

%{%}

%test
