cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote
% cd C:\Users\Utilizador\Documents\GitHub\GMote;
 
%Names of the gestures being trained
gesture = {'pictures'; 'video';  'music'; 'settings'; 'play_pause'; 'next'; 'previous'; %'fullscreen'
    };

%How many getures
number_of_gestures = length(gesture);

%{
%number of HMM training samples per gesture
number_of_samples = 40;

%cell matrix holding HMM training data
idx = cell(number_of_gestures, number_of_samples) ;

%number of centroids when doing Vector quantization, whcih in turn
%represents the number of elements in the codebook
codebookSize = 2^5;

%for every gesture and for every sample, read the apropriate file
for k = 1 : number_of_gestures
    for i = 1 : number_of_samples
        idx{k, i} = getDataFromFile(gesture{k}, i, 'idx') + 1;
    end
end
%}

% %{
%number of HMM training samples per gesture
number_of_cdbk_samples = 10;

%cell matrix holding all codebook building data
sample = cell(number_of_gestures, number_of_samples);

%there's no way to know the size of the data vector so just declare it
codebookData = [];

%for every gesture and for every sample put data into the data vector
for k = 1 : number_of_gestures
    for i = 1 : number_of_cdbk_samples
        sample{k, i} = getDataFromFile(gesture{k}, i, 'codebook');
        codebookData = [codebookData; sample{k, i}];
    end
end

%perform the vector quantization, the output: m, are the codebookSize
%centroids of the codebookData points
[m, ~, ~] = vqsplit(codebookData', codebookSize);

%create Kd-tree with the points obtained previously
codebook = KDTreeSearcher(m');

%}