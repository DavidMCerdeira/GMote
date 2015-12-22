lp = fir1(8, 0.1);
%%{
gesture = 'pictures';

cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote

circ_gest1 = getDataFromFile(gesture, 1);
circ_gest2 = getDataFromFile(gesture, 2);
circ_gest3 = getDataFromFile(gesture, 3);
circ_gest4 = getDataFromFile(gesture, 4);
circ_gest5 = getDataFromFile(gesture, 5);
circ_gest6 = getDataFromFile(gesture, 6);
circ_gest7 = getDataFromFile(gesture, 7);
circ_gest8 = getDataFromFile(gesture, 8);
circ_gest9 = getDataFromFile(gesture, 9);
%circ_gest10 = getDataFromFile(gesture, 10);
%{
circ_gest1 = filter(lp, 1, circ_gest1);
circ_gest2 = filter(lp, 1, circ_gest2);
circ_gest3 = filter(lp, 1, circ_gest3);
circ_gest4 = filter(lp, 1, circ_gest4);
circ_gest5 = filter(lp, 1, circ_gest5);
circ_gest6 = filter(lp, 1, circ_gest6);
circ_gest7 = filter(lp, 1, circ_gest7);
circ_gest8 = filter(lp, 1, circ_gest8);
circ_gest9 = filter(lp, 1, circ_gest9);
%}
%}
% %{
gesture = 'video';
vi_gest1 = getDataFromFile(gesture, 1);
vi_gest2 = getDataFromFile(gesture, 2);
vi_gest3 = getDataFromFile(gesture, 3);
vi_gest4 = getDataFromFile(gesture, 4);
vi_gest5 = getDataFromFile(gesture, 5);
vi_gest6 = getDataFromFile(gesture, 6);
vi_gest7 = getDataFromFile(gesture, 7);
vi_gest8 = getDataFromFile(gesture, 8);
vi_gest9 = getDataFromFile(gesture, 9);
%vi_gest10 = getDataFromFile(vi_gesture, 10);
%{
vi_gest1 = filter(lp, 1, vi_gest1);
vi_gest2 = filter(lp, 1, vi_gest2);
vi_gest3 = filter(lp, 1, vi_gest3);
vi_gest4 = filter(lp, 1, vi_gest4);
vi_gest5 = filter(lp, 1, vi_gest5);
vi_gest6 = filter(lp, 1, vi_gest6);
vi_gest7 = filter(lp, 1, vi_gest7);
vi_gest8 = filter(lp, 1, vi_gest8);
vi_gest9 = filter(lp, 1, vi_gest9);
%}

gesture = 'music';
mu_gest1 = getDataFromFile(gesture, 1);
mu_gest2 = getDataFromFile(gesture, 2);
mu_gest3 = getDataFromFile(gesture, 3);
mu_gest4 = getDataFromFile(gesture, 4);
mu_gest5 = getDataFromFile(gesture, 5);
mu_gest6 = getDataFromFile(gesture, 6);
mu_gest7 = getDataFromFile(gesture, 7);
mu_gest8 = getDataFromFile(gesture, 8);
mu_gest9 = getDataFromFile(gesture, 9);

gesture = 'settings';
se_gest1 = getDataFromFile(gesture, 1);
se_gest2 = getDataFromFile(gesture, 2);
se_gest3 = getDataFromFile(gesture, 3);
se_gest4 = getDataFromFile(gesture, 4);
se_gest5 = getDataFromFile(gesture, 5);
se_gest6 = getDataFromFile(gesture, 6);
se_gest7 = getDataFromFile(gesture, 7);
se_gest8 = getDataFromFile(gesture, 8);
se_gest9 = getDataFromFile(gesture, 9);

gesture = 'play_pause';
pp_gest1 = getDataFromFile(gesture, 1);
pp_gest2 = getDataFromFile(gesture, 2);
pp_gest3 = getDataFromFile(gesture, 3);
pp_gest4 = getDataFromFile(gesture, 4);
pp_gest5 = getDataFromFile(gesture, 5);
pp_gest6 = getDataFromFile(gesture, 6);
pp_gest7 = getDataFromFile(gesture, 7);
pp_gest8 = getDataFromFile(gesture, 8);
pp_gest9 = getDataFromFile(gesture, 9);

gesture = 'next';
nx_gest1 = getDataFromFile(gesture, 1);
nx_gest2 = getDataFromFile(gesture, 2);
nx_gest3 = getDataFromFile(gesture, 3);
nx_gest4 = getDataFromFile(gesture, 4);
nx_gest5 = getDataFromFile(gesture, 5);
nx_gest6 = getDataFromFile(gesture, 6);
nx_gest7 = getDataFromFile(gesture, 7);
nx_gest8 = getDataFromFile(gesture, 8);
nx_gest9 = getDataFromFile(gesture, 9);

gesture = 'previous';
pr_gest1 = getDataFromFile(gesture, 1);
pr_gest2 = getDataFromFile(gesture, 2);
pr_gest3 = getDataFromFile(gesture, 3);
pr_gest4 = getDataFromFile(gesture, 4);
pr_gest5 = getDataFromFile(gesture, 5);
pr_gest6 = getDataFromFile(gesture, 6);
pr_gest7 = getDataFromFile(gesture, 7);
pr_gest8 = getDataFromFile(gesture, 8);
pr_gest9 = getDataFromFile(gesture, 9);

