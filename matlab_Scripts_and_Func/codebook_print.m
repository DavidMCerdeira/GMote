fileIDCDBKh = fopen('.//GMOTE//Inc//codebook_param.h', 'wt');

fprintf(fileIDHMMh, '#ifndef _CDBK_PARAM_H\n');
fprintf(fileIDHMMh, '#define _CDBK_PARAM_H\n\n');

fprintf(fileIDCDBKh, '#define CDBK_SIZE %d\n', codebookSize);
fprintf(fileIDCDBKh, '#define NR_OF_DIM %d\n\n', 6);
fprintf(fileIDCDBKh, 'extern const float codeBookData[CDBK_SIZE][NR_OF_DIM];\n');

fprintf(fileIDCDBKh, '\n#endif\n');

fclose(fileIDCDBKh);

fileIDCDBKc = fopen('.//GMOTE//Src//codebook_param.c', 'wt');
fprintf(fileIDCDBKc, '#include "HMM_param.h"\n');

fprintf(fileIDCDBKc, '\n\n');
fprintf(fileIDCDBKc, 'const float codeBookData[CDBK_SIZE][NR_OF_DIM]={\n');
for i = 1 : codebookSize
    fprintf(fileIDCDBKc, '{');
    for j = 1 : 6
        fprintf(fileIDCDBKc, '%012f', m(j, i));
        if j ~= 6
            fprintf(fileIDCDBKc, ', ');
        end
    end
    
    if i ~= codebookSize
        fprintf(fileIDCDBKc, '},\n');
    else
        fprintf(fileIDCDBKc, '}');
    end
end
fprintf(fileIDCDBKc, '\n};\n\n');
fclose(fileIDCDBKc);