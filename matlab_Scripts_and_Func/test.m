Order = 8;
O = Order;

lp = fir1(O, 0.1);

filter(lp, 1, vi_gest1);
idx = knnsearch(md1, vi_gest1); 
fprintf('Problem 1 vi_gest1: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest2);
idx = knnsearch(md1, vi_gest2); 
fprintf('Problem 1 vi_gest2: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest3);
idx = knnsearch(md1, vi_gest3); 
fprintf('Problem 1 vi_gest3: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest4);
idx = knnsearch(md1, vi_gest4); 
fprintf('Problem 1 vi_gest4: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest5);
idx = knnsearch(md1, vi_gest5); 
fprintf('Problem 1 vi_gest5: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest6);
idx = knnsearch(md1, vi_gest6); 
fprintf('Problem 1 vi_gest6: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest7);
idx = knnsearch(md1, vi_gest7); 
fprintf('Problem 1 vi_gest7: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest8);
idx = knnsearch(md1, vi_gest8); 
fprintf('Problem 1 vi_gest8: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest9);
idx = knnsearch(md1, vi_gest9); 
fprintf('Problem 1 vi_gest9: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest1);
idx = knnsearch(md1, circ_gest1); 
fprintf('Problem 1 circ_gest1: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest2);
idx = knnsearch(md1, circ_gest2); 
fprintf('Problem 1 circ_gest2: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest3);
idx = knnsearch(md1, circ_gest3); 
fprintf('Problem 1 circ_gest3: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest4);
idx = knnsearch(md1, circ_gest4); 
fprintf('Problem 1 circ_gest4: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest5);
idx = knnsearch(md1, circ_gest5); 
fprintf('Problem 1 circ_gest5: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest6);
idx = knnsearch(md1, circ_gest6); 
fprintf('Problem 1 circ_gest6: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, vi_gest7);
idx = knnsearch(md1, circ_gest7); 
fprintf('Problem 1 circ_gest7: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest8);
idx = knnsearch(md1, circ_gest8); 
fprintf('Problem 1 circ_gest8: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);

filter(lp, 1, circ_gest9);
idx = knnsearch(md1, circ_gest9); 
fprintf('Problem 1 circ_gest9: '); 
P = h.problem1(idx); 
fprintf('%f\n', P);