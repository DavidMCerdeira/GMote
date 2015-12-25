fileID = fopen('.//GMOTE//Src//HMM_param.c', 'wt');

fprintf(fileID, '#include "HMM_param.h"\n');

fprintf(fileID, '\n\n');
%{
fprintf(fileID, 'const float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printA(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
%}
% %{
fprintf(fileID, 'const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printAT(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
%}
fprintf(fileID, '\n};\n\n');

%{
fprintf(fileID, 'const float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE]={\n');
for i = 1 : number_of_gestures
    h{i}.printB(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
%}
% %{
fprintf(fileID, 'const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printBT(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
%}
fprintf(fileID, '\n};\n\n');
 
fprintf(fileID, 'const float Pi[NUM_GEST][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printPi(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
fprintf(fileID, '\n};\n\n');

fprintf(fileID, 'const float codeBookData[CDBK_SIZE][NR_OF_DIM]={\n');
for i = 1 : codebookSize
    fprintf(fileID, '{');
    for j = 1 : 6
        fprintf(fileID, '%012f', m(j, i));
        if j ~= 6
            fprintf(fileID, ', ');
        end
    end
    
    if i ~= codebookSize
        fprintf(fileID, '},\n');
    else
        fprintf(fileID, '}');
    end
end
fprintf(fileID, '\n};\n\n');
fclose(fileID);

fileID = fopen('.//GMOTE//Inc//HMM_param.h', 'wt');
fprintf(fileID, '#ifndef _HMM_PARAM_H\n');
fprintf(fileID, '#define _HMM_PARAM_H\n\n');

fprintf(fileID, '#define NR_OF_STATES %d\n', states);
fprintf(fileID, '#define CDBK_SIZE %d\n', codebookSize);
fprintf(fileID, '#define NR_OF_DIM %d\n\n', 6);

fprintf(fileID, 'enum gest {');
for i = 1 : number_of_gestures
    fprintf(fileID, '%s', gesture{i});
    if i == 1
        fprintf(fileID, ' = 0, ');
    else
       fprintf(fileID, ', ');
    end
end

fprintf(fileID, 'NUM_GEST};\n');
fprintf(fileID, 'typedef enum gest gest;\n\n');
fprintf(fileID, 'extern const float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES];\n');
fprintf(fileID, 'extern const float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE];\n');
fprintf(fileID, 'extern const float Pi[NUM_GEST][NR_OF_STATES];\n');
fprintf(fileID, 'extern const float codeBookData[CDBK_SIZE][NR_OF_DIM];\n');
fprintf(fileID, '\n#endif\n');
fclose(fileID);
