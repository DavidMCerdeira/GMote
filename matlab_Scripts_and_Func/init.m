cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote
% cd C:\Users\Utilizador\Documents\GitHub\GMote;
 
gesture = {'pictures'; 'video';  'music'; 'settings'; 'play_pause'; 'fullscreen';'next'; 'previous'
    };
number_of_samples = 40;
number_of_gestures = length(gesture);

idx = cell(number_of_gestures, number_of_samples) ;
sample = cell(number_of_gestures, number_of_samples);

codebookData = [];
codebookSize = 2^5;

% %{
for k = 1 : number_of_gestures
    for i = 1 : number_of_samples
        idx{k, i} = getDataFromFile(gesture{k}, i, 'idx') + 1;
    end
end
%}

%{
lp = fir1(8, 0.1);
for k = 1 : number_of_gestures
    for i = 1 : 10
        sample{k, i} = getDataFromFile(gesture{k}, i, 'codebook');
        %sample{k, i} = filter(lp, 1, sample{k,i});
        codebookData = [codebookData; sample{k, i}];
    end
end
[m, ~, ~] = vqsplit(codebookData', codebookSize);

codebook = KDTreeSearcher(m');
%}