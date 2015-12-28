
wat = sample{3, 1};
ix = idx{3,1};
%{
for i = 1 : 120
    fprintf('{');
    for j = 1 : 6
        %fprintf('%+6.0f', wat(i, j));
        if j ~= 6
            fprintf(', ');
        end
    end
    if i ~= 120
        fprintf('},\n');
    else
        fprintf('}\n');
    end
end
%}

% %{
i = 1;
while i <= 120
    fprintf('{');
    save = i;
    for j = i : save + 19
        fprintf('%+3.0f', ix(j)-1);
        if j ~= (save+19)
            fprintf(', ');
        end
    end
    
    i = i + 20;
    
    if i ~= 120
        fprintf('},\n');
    else
        fprintf('}\n');
    end
end
%}