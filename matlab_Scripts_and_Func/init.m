lp = fir1(8, 0.1);
%%{
circ_gesture = 'pictures';

cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote

circ_gest1 = getDataFromFile(circ_gesture, 1);
circ_gest2 = getDataFromFile(circ_gesture, 2);
circ_gest3 = getDataFromFile(circ_gesture, 3);
circ_gest4 = getDataFromFile(circ_gesture, 4);
circ_gest5 = getDataFromFile(circ_gesture, 5);
circ_gest6 = getDataFromFile(circ_gesture, 6);
circ_gest7 = getDataFromFile(circ_gesture, 7);
circ_gest8 = getDataFromFile(circ_gesture, 8);
circ_gest9 = getDataFromFile(circ_gesture, 9);
%circ_gest10 = getDataFromFile(circ_gesture, 10);
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
vi_gesture = 'video';

vi_gest1 = getDataFromFile(vi_gesture, 1);
vi_gest2 = getDataFromFile(vi_gesture, 2);
vi_gest3 = getDataFromFile(vi_gesture, 3);
vi_gest4 = getDataFromFile(vi_gesture, 4);
vi_gest5 = getDataFromFile(vi_gesture, 5);
vi_gest6 = getDataFromFile(vi_gesture, 6);
vi_gest7 = getDataFromFile(vi_gesture, 7);
vi_gest8 = getDataFromFile(vi_gesture, 8);
vi_gest9 = getDataFromFile(vi_gesture, 9);
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