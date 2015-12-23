function data = getDataFromFile(gest, sampleNr)
    cd C:\Users\Utilizador\Documents\GitHub\GMote;

    file = sprintf('.\\TrainingData\\%s\\%d.csv', gest, sampleNr); 
    data = csvread(file);
end