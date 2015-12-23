    %%{
    clear vi_h
    vi_codebookSize = 2^4;

    vi_h = HMM(vi_gesture, 6, vi_codebookSize);
    vi_count = 1;

    %vector quantization
    [vi_m, vi_p, vi_distor] = vqsplit([
                              vi_gest1;...

                              vi_gest2;...

                              vi_gest3;...

                              vi_gest4;...

                              vi_gest5;...

                              vi_gest6;...

                              vi_gest7;...

                              vi_gest8;...

                              vi_gest9;...
                               %{%}
                             ]', vi_codebookSize);

    vi_md1 = KDTreeSearcher(vi_m'); % grow a kd-tree 
    %}
    % training

    %{
    idx = knnsearch(md1, gest1); % match points with index
    fprintf('Train %d:\n', count);
    h.scaling = 1;
    h.train_one(idx);
    %}

    vi_idx1 = knnsearch(vi_md1, vi_gest1); % match points with index
    vi_idx2 = knnsearch(vi_md1, vi_gest2); % match points with index
    vi_idx3 = knnsearch(vi_md1, vi_gest3); % match points with index
    vi_idx4 = knnsearch(vi_md1, vi_gest4); % match points with index
    vi_idx5 = knnsearch(vi_md1, vi_gest5); % match points with index
    vi_idx6 = knnsearch(vi_md1, vi_gest6); % match points with index
    vi_idx7 = knnsearch(vi_md1, vi_gest7); % match points with index
    vi_idx8 = knnsearch(vi_md1, vi_gest8); % match points with index
    vi_idx9 = knnsearch(vi_md1, vi_gest9); % match points with index

    %{
    fprintf('Train %d:\n', vi_count);
    vi_h.train_multiple(vi_idx1);
    vi_count = vi_count + 1;
    %}

    fprintf('Train %d:\n', vi_count);
    vi_h.train_multiple(vi_idx2);
    vi_count = vi_count + 1;

    fprintf('Train %d:\n', vi_count);
    vi_h.train_multiple(vi_idx3);
    vi_count = vi_count + 1;

    fprintf('Train %d:\n', vi_count);
    vi_h.train_multiple(vi_idx4);
    vi_count = vi_count + 1;

    fprintf('Train %d:\n', vi_count);
    vi_h.train_multiple(vi_idx5);
    vi_count = vi_count + 1;

    fprintf('Train %d:\n', vi_count);
    vi_h.train_multiple(vi_idx6);
    vi_count = vi_count + 1;
    %{%}
    vi_h.commit_mutiple();
    %}
    fprintf('Done!\n');