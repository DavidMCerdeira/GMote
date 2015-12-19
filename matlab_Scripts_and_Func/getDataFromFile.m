function data = getDataFromFile(gest, sampleNr)
    file = sprintf('.\\TrainingData\\%s\\Sample%d.csv', gest, sampleNr); 
    data = csvread(file);
end