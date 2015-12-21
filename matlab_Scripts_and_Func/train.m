%%{
clear h;
codebookSize = 2^1;

h = HMM(gesture, 2, codebookSize);
count = 1;

%vector quantization
[m, p, distor] = vqsplit([
                          gest1;...
                         %{  
                          gest2;...
                         
                          gest3;...
                        
                          gest4;...
                          
                          gest5;...
                          
                          gest6;...
                          
                          gest7;...
                          
                          gest8;...
                          
                          gest9;...
                          %}
                         ]', codebookSize);

md1 = KDTreeSearcher(m'); % grow a kd-tree 
%}
% training

%{
idx = knnsearch(md1, gest1); % match points with index
fprintf('Train %d:\n', count);
h.train_one(idx);
%}

%  %{
idx = knnsearch(md1, gest1); % match points with index
fprintf('Train %d:\n', count);
h.train_multiple(idx);
count = count + 1;

idx = knnsearch(md1, gest2); % match points with index
fprintf('Train %d:\n', count);
h.train_multiple(idx);
count = count + 1;
%{
idx = knnsearch(md1, gest3); % match points with index
fprintf('Train %d:\n', count);
h.train_multiple(idx);
count = count + 1;

idx = knnsearch(md1, gest4); % match points with index
fprintf('Train %d:\n', count);
h.train_multiple(idx);
count = count + 1;

idx = knnsearch(md1, gest5); % match points with index
fprintf('Train %d:\n', count);
h.train_multiple(idx);
count = count + 1;

idx = knnsearch(md1, gest6); % match points with index
fprintf('Train %d:\n', count);
h.train_multiple(idx);
count = count + 1;
%}
h.commit_mutiple();
%}
fprintf('Done!\n');