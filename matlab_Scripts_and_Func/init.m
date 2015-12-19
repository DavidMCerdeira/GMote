
gesture = 'circle';


cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote

gest1 = getDataFromFile(gesture, 1);
gest2 = getDataFromFile(gesture, 2);
gest3 = getDataFromFile(gesture, 3);
gest4 = getDataFromFile(gesture, 4);
gest5 = getDataFromFile(gesture, 5);
gest6 = getDataFromFile(gesture, 6);
gest7 = getDataFromFile(gesture, 7);
gest8 = getDataFromFile(gesture, 8);
gest9 = getDataFromFile(gesture, 9);
%gest10 = getDataFromFile(gesture, 10);


clear h;
codebookSize = 2^4;
h = HMM(gesture, 4, codebookSize);
count = 1;

[m, p, distor] = vqsplit([gest1]', codebookSize); %one training set
md1 = KDTreeSearcher(m'); % grow a kd-tree 


