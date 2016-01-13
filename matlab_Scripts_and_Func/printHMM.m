fileIDHMMc = fopen('.//GMOTE//Src//HMM_param.c', 'wt');
fileIDHMMh = fopen('.//GMOTE//Inc//HMM_param.h', 'wt');

fprintf(fileIDHMMh, '#ifndef _HMM_PARAM_H\n');
fprintf(fileIDHMMh, '#define _HMM_PARAM_H\n\n');

fprintf(fileIDHMMh, '#include "HMM_param.h"\n');
fprintf(fileIDHMMh, '#include "codebook_param.h"\n');

fprintf(fileIDHMMh, '#define NR_OF_STATES %d\n', states);

fprintf(fileIDHMMh, 'enum gest {');
for i = 1 : number_of_gestures
    fprintf(fileIDHMMh, '%s', gesture{i});
    if i == 1
        fprintf(fileIDHMMh, ' = 0, ');
    else
       fprintf(fileIDHMMh, ', ');
    end
end

fprintf(fileIDHMMh, 'NUM_GEST, NOT_RECOGNIZED};\n');
fprintf(fileIDHMMh, 'typedef enum gest gest;\n\n');

fprintf(fileIDHMMc, '#include "HMM_param.h"\n');

fprintf(fileIDHMMc, '\n\n');
%{
fprintf(fileIDHMMh, 'extern const float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES];\n');
fprintf(fileIDHMMc, 'const float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printA(fileIDHMMc);
    if i ~= number_of_gestures
        fprintf(fileIDHMMc, ',\n\n');
    end
end
%}
% %{
fprintf(fileIDHMMh, 'extern const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES];\n');
fprintf(fileIDHMMc, 'const float AT[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printAT(fileIDHMMc);
    if i ~= number_of_gestures
        fprintf(fileIDHMMc, ',\n\n');
    end
end
%}
fprintf(fileIDHMMc, '\n};\n\n');

%{
fprintf(fileIDHMMh, 'extern const float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE];\n');
fprintf(fileIDHMMc, 'const float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE]={\n');
for i = 1 : number_of_gestures
    h{i}.printB(fileIDHMMc);
    if i ~= number_of_gestures
        fprintf(fileIDHMMc, ',\n\n');
    end
end
%}
% %{
fprintf(fileIDHMMh, 'extern const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES];\n');
fprintf(fileIDHMMc, 'const float BT[NUM_GEST][CDBK_SIZE][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printBT(fileIDHMMc);
    if i ~= number_of_gestures
        fprintf(fileIDHMMc, ',\n\n');
    end
end
%}
fprintf(fileIDHMMc, '\n};\n\n');
fprintf(fileIDHMMh, 'extern const float Pi[NUM_GEST][NR_OF_STATES];\n');

fprintf(fileIDHMMh, '\n#endif\n');
fprintf(fileIDHMMc, 'const float Pi[NUM_GEST][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h{i}.printPi(fileIDHMMc);
    if i ~= number_of_gestures
        fprintf(fileIDHMMc, ',\n\n');
    end
end
fprintf(fileIDHMMc, '\n};\n\n');


fclose(fileIDHMMh);
fclose(fileIDHMMc);
