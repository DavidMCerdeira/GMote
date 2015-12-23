%quantos Gestos?
n_gest = 1;
for i = 1 : length(h)
    fprintf('HMM: %s\n', h(i).name);
    for j = 1 : length(h)
        fprintf('\tTesting data: %s\n', gesture{j});
        for k = 1 : number_of_samples
            idx = knnsearch(h(i).codebook, sample{j, k});             
            P = h(i).problem1(idx); 
            fprintf('\t\t%d: %f\n', k, P); 
        end
    end
end

fprintf('Done!\n\n');