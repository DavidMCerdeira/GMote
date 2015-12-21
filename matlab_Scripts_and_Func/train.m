%%{
clear h;
codebookSize = 2^4;

h = HMM(gesture, 3, codebookSize);
count = 1;

%vector quantization
[m, p, distor] = vqsplit([
                          circ_gest1;...
                          
                           circ_gest2;...
                        
                          circ_gest3;...
                        
                          circ_gest4;...
                          
                          circ_gest5;...
                          
                          circ_gest6;...
                          
                          circ_gest7;...
                          
                          circ_gest8;...
                          
                          circ_gest9;...
                           %{%}
                         ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree 
%}
% training

%{
idx = knnsearch(md1, gest1); % match points with index
fprintf('Train %d:\n', count);
h.scaling = 1;
h.train_one(idx);
%}

circ_idx1 = knnsearch(md1, circ_gest1); % match points with index
circ_idx2 = knnsearch(md1, circ_gest2); % match points with index
circ_idx3 = knnsearch(md1, circ_gest3); % match points with index
circ_idx4 = knnsearch(md1, circ_gest4); % match points with index
circ_idx5 = knnsearch(md1, circ_gest5); % match points with index
circ_idx6 = knnsearch(md1, circ_gest6); % match points with index
circ_idx7 = knnsearch(md1, circ_gest7); % match points with index
circ_idx8 = knnsearch(md1, circ_gest8); % match points with index
circ_idx9 = knnsearch(md1, circ_gest9); % match points with index

%{
fprintf('Train %d:\n', count);
h.train_multiple(idx1);
count = count + 1;
%}

fprintf('Train %d:\n', count);
h.train_multiple(idx2);
count = count + 1;

fprintf('Train %d:\n', count);
h.train_multiple(idx3);
count = count + 1;

fprintf('Train %d:\n', count);
h.train_multiple(idx4);
count = count + 1;

fprintf('Train %d:\n', count);
h.train_multiple(idx5);
count = count + 1;

fprintf('Train %d:\n', count);
h.train_multiple(idx6);
count = count + 1;
%{%}
h.commit_mutiple();
%}
fprintf('Done!\n');