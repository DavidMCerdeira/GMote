clear h
codebookSize = 2^4;
n_sates = 4;
count = 1;

% %{ 
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

h(count) = HMM(gesture, n_sates, codebookSize, md, 75);
idx = knnsearch( h(count).codebook, circ_gest1 ); % match points with index
fprintf('Training %s\n', gesture);
h(count).train_one(idx);
count = count + 1;
%}

% %{
gesture = 'video';
%vector quantization
[m, ~, ~] = vqsplit([
    %vi_gest1;
    
    %vi_gest2;
    
    %vi_gest3;
    
    %vi_gest4;

    vi_gest5;
%{
    vi_gest6;

    vi_gest7;

    vi_gest8;

    vi_gest9;
    %}
    ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree
h(count) = HMM(gesture, n_sates, codebookSize, md1, 30);
idx = knnsearch(h(count).codebook, vi_gest7); % match points with index
fprintf('Training %s\n', gesture);
h(count).train_one(idx);
count = count + 1;
%}

% %{
gesture = 'music';
%vector quantization
[m, ~, ~] = vqsplit([
    %mu_gest1;
    
    %mu_gest2;
    
    %mu_gest3;
    
    %mu_gest4;

    mu_gest5;
%{
    mu_gest6;

    mu_gest7;

    mu_gest8;

    mu_gest9;
    %}
    ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree
h(count) = HMM(gesture, n_sates, codebookSize, md1, 30);
idx = knnsearch(h(count).codebook, mu_gest7); % match points with index
fprintf('Training %s\n', gesture);
h(count).train_one(idx);
count = count + 1;
%}

% %{
gesture = 'settings';
%vector quantization
[m, ~, ~] = vqsplit([
    %se_gest1;
    
    %se_gest2;
    
    %se_gest3;
    
    %se_gest4;

    se_gest5;
%{
    se_gest6;

    se_gest7;

    se_gest8;

    se_gest9;
    %}
    ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree
h(count) = HMM(gesture, n_sates, codebookSize, md1, 30);
idx = knnsearch(h(count).codebook, se_gest7); % match points with index
fprintf('Training %s\n', gesture);
h(count).train_one(idx);
count = count + 1;
%}

% %{
gesture = 'play_pause';
%vector quantization
[m, ~, ~] = vqsplit([
    %pp_gest1;
    
    %pp_gest2;
    
    %pp_gest3;
    
    %pp_gest4;

    pp_gest5;
%{
    pp_gest6;

    pp_gest7;

    pp_gest8;

    pp_gest9;
    %}
    ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree
h(count) = HMM(gesture, n_sates, codebookSize, md1, 30);
idx = knnsearch(h(count).codebook, pp_gest7); % match points with index
fprintf('Training %s\n', gesture);
h(count).train_one(idx);
count = count + 1;
%}

% %{
gesture = 'next';
%vector quantization
[m, ~, ~] = vqsplit([
    %nx_gest1;
    
    %nx_gest2;
    
    %nx_gest3;
    
    %nx_gest4;

    nx_gest5;
%{
    nx_gest6;

    nx_gest7;

    nx_gest8;

    nx_gest9;
    %}
    ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree
h(count) = HMM(gesture, n_sates, codebookSize, md1, 30);
idx = knnsearch(h(count).codebook, nx_gest7); % match points with index
fprintf('Training %s\n', gesture);
h(count).train_one(idx);
count = count + 1;
%}

% %{
gesture = 'previous';
%vector quantization
[m, ~, ~] = vqsplit([
    %pr_gest1;
    
    %pr_gest2;
    
    %pr_gest3;
    
    %pr_gest4;

    pr_gest5;
%{
    pr_gest6;

    pr_gest7;

    pr_gest8;

    pr_gest9;
    %}
    ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree
h(count) = HMM(gesture, n_sates, codebookSize, md1, 30);
idx = knnsearch(h(count).codebook, pr_gest7); % match points with index
fprintf('Training %s\n', gesture);
h(count).train_one(idx);
count = count + 1;
%}
fprintf('Done!\n');

test