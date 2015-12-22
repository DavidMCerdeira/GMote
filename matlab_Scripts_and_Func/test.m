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
    
    idx = knnsearch(h(i).codebook, mu_gest1); 
    fprintf('mu_gest1: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest2); 
    fprintf('mu_gest2: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest3); 
    fprintf('mu_gest3: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest4); 
    fprintf('mu_gest4: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest5); 
    fprintf('mu_gest5: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest6); 
    fprintf('mu_gest6: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest7); 
    fprintf('mu_gest7: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest8); 
    fprintf('mu_gest8: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, mu_gest9); 
    fprintf('mu_gest9: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n\n', P);
    
    idx = knnsearch(h(i).codebook, se_gest1); 
    fprintf('se_gest1: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest2); 
    fprintf('se_gest2: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest3); 
    fprintf('se_gest3: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest4); 
    fprintf('se_gest4: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest5); 
    fprintf('se_gest5: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest6); 
    fprintf('se_gest6: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest7); 
    fprintf('se_gest7: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest8); 
    fprintf('se_gest8: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, se_gest9); 
    fprintf('circ_gest9: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n\n', P);
    
    idx = knnsearch(h(i).codebook, pp_gest1); 
    fprintf('pp_gest1: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest2); 
    fprintf('pp_gest2: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest3); 
    fprintf('pp_gest3: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest4); 
    fprintf('pp_gest4: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest5); 
    fprintf('pp_gest5: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest6); 
    fprintf('pp_gest6: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest7); 
    fprintf('pp_gest7: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest8); 
    fprintf('pp_gest8: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pp_gest9); 
    fprintf('ne_gest9: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n\n', P);
    
    idx = knnsearch(h(i).codebook, nx_gest1); 
    fprintf('nx_gest1: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest2); 
    fprintf('nx_gest2: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest3); 
    fprintf('nx_gest3: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest4); 
    fprintf('nx_gest4: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest5); 
    fprintf('nx_gest5: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest6); 
    fprintf('nx_gest6: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest7); 
    fprintf('nx_gest7: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest8); 
    fprintf('nx_gest8: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, nx_gest9); 
    fprintf('nx_gest9: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n\n', P);
    
    idx = knnsearch(h(i).codebook, pr_gest1); 
    fprintf('pr_gest1: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest2); 
    fprintf('pr_gest2: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest3); 
    fprintf('pr_gest3: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest4); 
    fprintf('pr_gest4: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest5); 
    fprintf('pr_gest5: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest6); 
    fprintf('pr_gest6: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest7); 
    fprintf('pr_gest7: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest8); 
    fprintf('pr_gest8: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n', P);

    idx = knnsearch(h(i).codebook, pr_gest9); 
    fprintf('pr_gest9: '); 
    P = h(i).problem1(idx); 
    fprintf('%f\n\n', P);
end

fprintf('Done!\n\n');