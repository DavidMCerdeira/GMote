function data = getDataFromFile(gest, sampleNr)
    file = sprintf('.\\TrainingData\\%s\\%d.csv', gest, sampleNr); 
    data = csvread(file);
end