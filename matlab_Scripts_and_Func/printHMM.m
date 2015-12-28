fileIDc = fopen('.//GMOTE//Src//HMM_param.c', 'wt');
fileIDh = fopen('.//GMOTE//Inc//HMM_param.h', 'wt');

fprintf(fileIDh, '#ifndef _HMM_PARAM_H\n');
fprintf(fileIDh, '#define _HMM_PARAM_H\n\n');

fprintf(fileIDh, '#define NR_OF_STATES %d\n', states);
fprintf(fileIDh, '#define CDBK_SIZE %d\n', codebookSize);
fprintf(fileIDh, '#define NR_OF_DIM %d\n\n', 6);

fprintf(fileIDh, 'enum gest {');
for i = 1 : number_of_gestures
    fprintf(fileIDh, '%s', gesture{i});
    if i == 1
        fprintf(fileIDh, ' = 0, ');
    else
       fprintf(fileIDh, ', ');
    end
end

fprintf(fileIDh, 'NUM_GEST, NOT_RECOGNIZED};\n');
fprintf(fileIDh, 'typedef enum gest gest;\n\n');


fprintf(fileIDc, '#include "HMM_param.h"\n');

fprintf(fileIDc, '\n\n');
%{
fprintf(fileIDh, 'extern const float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES];\n');
fprintf(fileIDc, 'const float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printA(fileIDc);
    if i ~= number_of_gestures
        fprintf(fileIDc, ',\n\n');
    end
end
%}
% %{
fprintf(fileIDh, 'extern const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES];\n');
fprintf(fileIDc, 'const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printAT(fileIDc);
    if i ~= number_of_gestures
        fprintf(fileIDc, ',\n\n');
    end
end
%}
fprintf(fileIDc, '\n};\n\n');

%{
fprintf(fileIDh, 'extern const float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE];\n');
fprintf(fileIDc, 'const float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE]={\n');
for i = 1 : number_of_gestures
    h{i}.printB(fileIDc);
    if i ~= number_of_gestures
        fprintf(fileIDc, ',\n\n');
    end
end
%}
% %{
fprintf(fileIDh, 'extern const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES];\n');
fprintf(fileIDc, 'const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printBT(fileIDc);
    if i ~= number_of_gestures
        fprintf(fileIDc, ',\n\n');
    end
end
%}
fprintf(fileIDc, '\n};\n\n');
 
fprintf(fileIDc, 'const float Pi[NUM_GEST][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printPi(fileIDc);
    if i ~= number_of_gestures
        fprintf(fileIDc, ',\n\n');
    end
end
fprintf(fileIDc, '\n};\n\n');

fprintf(fileIDc, 'const float codeBookData[CDBK_SIZE][NR_OF_DIM]={\n');
for i = 1 : codebookSize
    fprintf(fileIDc, '{');
    for j = 1 : 6
        fprintf(fileIDc, '%012f', m(j, i));
        if j ~= 6
            fprintf(fileIDc, ', ');
        end
    end
    
    if i ~= codebookSize
        fprintf(fileIDc, '},\n');
    else
        fprintf(fileIDc, '}');
    end
end
fprintf(fileIDc, '\n};\n\n');
fclose(fileIDc);


fprintf(fileIDh, 'extern const float Pi[NUM_GEST][NR_OF_STATES];\n');
fprintf(fileIDh, 'extern const float codeBookData[CDBK_SIZE][NR_OF_DIM];\n');
fprintf(fileIDh, '\n#endif\n');
fclose(fileIDh);
