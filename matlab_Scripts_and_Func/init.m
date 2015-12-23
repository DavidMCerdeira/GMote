cd E:\Universidade\MESTRADO_EEIC\ProjectoI\GMote

gesture = {'pictures'; 'video';  'music'; 'settings'; 'play_pause'; 'next'; 'previous'};
number_of_samples = 9;
number_of_gestures = 7;

sample = cell(number_of_gestures, number_of_samples);

for k = 1 : 7
    for i = 1 : number_of_samples
        sample{k, i} = getDataFromFile(gesture{k}, i);
    end
end
%circ_gest10 = getDataFromFile(gesture, 10);