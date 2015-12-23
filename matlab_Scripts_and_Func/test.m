%quantos Gestos?
n_gest = 1;
results = zeros(number_of_samples, number_of_gestures, length(h));

threshold = -400;

%%{
for pk = 1 : 2
    if pk == 1
        fprintf('Matlab:\n');
    else
        fprintf('GMote:\n');
    end
for i = 1 : length(h)
    %fprintf('HMM: %s\n', h{i}.name);
    for j = 1 : 7
        %fprintf('\t')
        if j == i
            %fprintf('*');
        end
        %fprintf('Testing data: %s\n', gesture{j});
        for k = 1 : number_of_samples
            if pk == 1
                [~, P] = hmmdecode(idx{j, k}', h{i}.A, h{i}.b);
            else
                P = h{i}.problem1(idx{j,k});
            end
            if P < threshold
                P = NaN;
            end
            
            results(k, j, i) = P;
        end
    end
end
%}

%fprintf('\n');

avg = zeros(length(h), length(h));
for i = 1 : length(h)
    for j = 1 : 7
        avg(i,j) = nanmean(results(:,j,i));
    end
end

for i = 1 : length(h)
    fprintf('*%10s(%08.2f) NaN(%d/%d)\n', h{i}.name, avg(i,i), sum(isnan(results(:,i,i))), number_of_samples);
    base = avg(i,i);
    for j = 1 : 7
        if avg(i,j) > base
            fprintf(' %10s(%08.2f) NaN(%d/%d) is more likely\n', gesture{j}, avg(i,j), sum(isnan(results(:,j,i))), number_of_samples);
        end
    end
    fprintf('\n');
end
end

fprintf('Done!\n\n');
