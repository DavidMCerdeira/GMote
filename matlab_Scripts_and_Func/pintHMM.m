fileID = fopen('./HMM_param.h', 'wt');

fprintf(fileID, '#define NUM_GEST %d\n', number_of_gestures);
fprintf(fileID, '#define NR_OF_STATES %d\n', n_sates);
fprintf(fileID, '#define CDBK_SIZE %d\n', codebookSize);
fprintf(fileID, '#define NR_OF_DIM %d\n', 6);

fprintf(fileID, '\n\n');
fprintf(fileID, 'float A[NUM_GEST][NR_OF_STATES][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h(i).printA(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
fprintf(fileID, '\n}\n\n');

fprintf(fileID, 'float B[NUM_GEST][NR_OF_STATES][CDBK_SIZE]={\n');
for i = 1 : number_of_gestures
    h(i).printB(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
fprintf(fileID, '\n}\n\n');
 
fprintf(fileID, 'float Pi[NUM_GEST][NR_OF_STATES]={\n');
for i = 1 : number_of_gestures
    h(i).printPi(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
fprintf(fileID, '\n}\n\n');

fprintf(fileID, 'float codeBookData[NUM_GEST][NR_OF_DIM]={\n');
for i = 1 : number_of_gestures
    h(i).printCodeBook(fileID);
    if i ~= number_of_gestures
        fprintf(fileID, ',\n\n');
    end
end
fprintf(fileID, '\n}\n\n');
fclose(fileID);