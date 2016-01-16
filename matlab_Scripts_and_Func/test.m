
%Matrix holding probability values of each model against all acquired
%gestures
results = zeros(number_of_samples, number_of_gestures, length(h));

%Probabilities above this treshold will be considered NaN
threshold = -400;

%Test gestures against Matlab implemention and our implementation
for pk = 1 : 2
    if pk == 1
        fprintf('Matlab:\n');
    else
        fprintf('GMote:\n');
    end
    for i = 1 : number_of_gestures
        for j = 1 : number_of_gestures
            for k = 1 : number_of_samples
                if pk == 1 %Matlab's implementation
                    [~, P] = hmmdecode(idx{j, k}', h{i}.A, h{i}.b);
                else %our implementation
                    P = h{i}.problem1(idx{j,k});
                end
                
                if P < threshold
                    P = NaN;
                end
                
                %save probability of sample i from gesture j measured
                %against model k
                results(k, j, i) = P;
            end
        end
    end
    
    %allocate space to averages
    avg = zeros(length(h), length(h));
    for i = 1 : length(h)
        for j = 1 : length(h)
            %calculate mean withou including NaN
            avg(i,j) = nanmean(results(:,j,i));
        end
    end
    
    %for every gesture
    for i = 1 : length(h)
        fprintf('*%10s(%08.2f) NaN(%d/%d)\n', h{i}.name, avg(i,i), sum(isnan(results(:,i,i))), number_of_samples);
        base = avg(i,i); %average of the model's own gestures
        for j = 1 : length(h)
            %if gesture j is more likely
            if avg(i,j) > base && avg(i,j) > avg(j,j)
                fprintf(' %10s(%08.2f) NaN(%d/%d) is more likely\n', gesture{j}, avg(i,j), sum(isnan(results(:,j,i))), number_of_samples);
            end
        end
        fprintf('\n');
    end
end

fprintf('Done!\n\n');
