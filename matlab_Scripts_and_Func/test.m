%quantos Gestos?
n_gest  = 1;
for i = 1 : length(h)
    fprintf('HMM: %s\n', h(i).name);
    
    idx = knnsearch(h(i).codebook, vi_gest1); 
    fprintf('vi_gest1: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest2); 
    fprintf('vi_gest2: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest3); 
    fprintf('vi_gest3: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest4); 
    fprintf('vi_gest4: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest5); 
    fprintf('vi_gest5: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest6); 
    fprintf('vi_gest6: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest7); 
    fprintf('vi_gest7: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest8); 
    fprintf('vi_gest8: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, vi_gest9); 
    fprintf('vi_gest9: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest1); 
    fprintf('circ_gest1: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest2); 
    fprintf('circ_gest2: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest3); 
    fprintf('circ_gest3: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest4); 
    fprintf('circ_gest4: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest5); 
    fprintf('circ_gest5: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest6); 
    fprintf('circ_gest6: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest7); 
    fprintf('circ_gest7: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest8); 
    fprintf('circ_gest8: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, circ_gest9); 
    fprintf('circ_gest9: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n\n', P);
end

fprintf('Done!\n\n');