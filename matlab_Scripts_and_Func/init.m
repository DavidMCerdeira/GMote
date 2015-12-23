%cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote

gesture = {'pictures'; 'video';  'music'; 'settings'; 'play_pause'; 'next'; 'previous'};
number_of_samples = 9;
number_of_gestures = 5;


sample = cell(number_of_gestures, number_of_samples);

codebookData = [];
codebookSize = 2^5;

lp = fir1(8, 0.1);

for k = 1 : 7
    for i = 1 : number_of_samples
        sample{k, i} = getDataFromFile(gesture{k}, i);
        sample{k, i} = filter(lp, 1, sample{k,i});
        codebookData = [codebookData; sample{k, i}];
    end
end

[m, ~, ~] = vqsplit(codebookData', codebookSize);

codebook = KDTreeSearcher(m');

idx = knnsearch(codebook, sample{1, 2});

%circ_gest10 = getDataFromFile(gesture, 10);