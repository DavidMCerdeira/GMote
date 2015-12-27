    %%{
    clear circ_h;
    circ_codebookSize = 2^4;
    circ_gesture = 'circle';
    circ_h = HMM(circ_gesture, 3, circ_codebookSize);
    circ_count = 1;

    %vector quantization
    [circ_m, circ_p, circ_distor] = vqsplit([
                              circ_gest1;...

                              circ_gest2;...

                              circ_gest3;...

                              circ_gest4;...

                              circ_gest5;...
                              %{
                              circ_gest6;...

                              circ_gest7;...

                              circ_gest8;...

                              circ_gest9;...
                               %}
                             ]', circ_codebookSize);

    circ_md1 = KDTreeSearcher(circ_m'); % grow a kd-tree 
    %}
    % training

    %{
    circ_idx = knnsearch(circ_md1, circ_gest1); % match points with index
    fprintf('Train %d:\n', circ_count);
    circ_h.scaling = 1;
    circ_h.train_one(circ_idx);
    %}

    circ_idx1 = knnsearch(circ_md1, circ_gest1); % match points with index
    circ_idx2 = knnsearch(circ_md1, circ_gest2); % match points with index
    circ_idx3 = knnsearch(circ_md1, circ_gest3); % match points with index
    circ_idx4 = knnsearch(circ_md1, circ_gest4); % match points with index
    circ_idx5 = knnsearch(circ_md1, circ_gest5); % match points with index
    circ_idx6 = knnsearch(circ_md1, circ_gest6); % match points with index
    circ_idx7 = knnsearch(circ_md1, circ_gest7); % match points with index
    circ_idx8 = knnsearch(circ_md1, circ_gest8); % match points with index
    circ_idx9 = knnsearch(circ_md1, circ_gest9); % match points with index

    %{
    fprintf('Train %d:\n', circ_count);
    circ_h.train_multiple(circ_idx1);
    circ_count = count + 1;
    %}

    fprintf('Train %d:\n', circ_count);
    circ_h.train_multiple(circ_idx2);
    circ_count = circ_count + 1;

    fprintf('Train %d:\n', circ_count);
    circ_h.train_multiple(circ_idx3);
    circ_count = circ_count + 1;

    fprintf('Train %d:\n', circ_count);
    circ_h.train_multiple(circ_idx4);
    circ_count = circ_count + 1;

    fprintf('Train %d:\n', circ_count);
    circ_h.train_multiple(circ_idx5);
    circ_count = circ_count + 1;

    fprintf('Train %d:\n', circ_count);
    circ_h.train_multiple(circ_idx6);
    circ_count = circ_count + 1;
    %{%}
    circ_h.commit_mutiple();
    %}
    fprintf('Done!\n');

