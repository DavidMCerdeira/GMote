function data = getDataFromFile(gest, sampleNr, type)
    file = sprintf('.\\TrainingData\\%s\\%s\\%d.csv', type, gest, sampleNr); 
    data = csvread(file);
end