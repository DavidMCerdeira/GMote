function [f1, f2] = obsVec(A)
    f1 = std(A);
    f2 = mean(A);
end