clear h
codebookSize = 2^4;
n_sates = 4;
count = 1;


%{ 
gesture = 'pictures';
%vector quantization
[m, ~, ~] = vqsplit([
    circ_gest1;
    
    circ_gest2;
    
    circ_gest3;
    %{
    circ_gest4;

    circ_gest5;

    circ_gest6;

    circ_gest7;

    circ_gest8;

    circ_gest9;
    %}
    ]', codebookSize);
md = KDTreeSearcher(m'); % grow a kd-tree

h(count) = HMM(gesture, n_sates, codebookSize, md);
idx = knnsearch( h(count).codebook, circ_gest1 ); % match points with index
h(count).train_one(idx);
count = count + 1;
%}

% %{
gesture = 'video';
%vector quantization
[m, ~, ~] = vqsplit([
    %vi_gest1;
    
    vi_gest2;
    
    vi_gest3;
    
    vi_gest4;

    vi_gest5;

    vi_gest6;
%{
    vi_gest7;

    vi_gest8;

    vi_gest9;
    %}
    ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree
h(count) = HMM(gesture, n_sates, codebookSize, md1);
idx = knnsearch(h(count).codebook, vi_gest3); % match points with index
h(count).train_one(idx);
count = count + 1;
%}
fprintf('Done!\n');

test