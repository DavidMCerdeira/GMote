cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote
% cd C:\Users\Utilizador\Documents\GitHub\GMote;
 
gesture = {'pictures'; 'video';  'music'; 'settings'; 'play_pause'; 'fullscreen';'next'; 'previous'};
number_of_samples = 40;
number_of_gestures = 8;

idx = cell(number_of_gestures, number_of_samples) ;
sample = cell(number_of_gestures, number_of_samples);

codebookData = [];
codebookSize = 2^5;

lp = fir1(8, 0.1);

for k = 1 : number_of_gestures
    for i = 1 : number_of_samples
        idx{k, i} = getDataFromFile(gesture{k}, i) + 1;
        %sample{k, i} = filter(lp, 1, sample{k,i});
        %codebookData = [codebookData; sample{k, i}];
    end
end

% [m, ~, ~] = vqsplit(codebookData', codebookSize);
% 
% codebook = KDTreeSearcher(m');

% for k = 1 : 7
%     for i = 1 : number_of_samples
%         idx{k, i} = knnsearch(codebook, sample{k, i});
%     end
% end
%circ_gest10 = getDataFromFile(gesture, 10);