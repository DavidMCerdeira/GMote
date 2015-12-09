function [fr, N] = getFrames(A, overLap, frameSize)
    SIZE = length(A);
    N = (SIZE - frameSize)/(frameSize - overLap) + 1;
    fr = zeros(N, frameSize);
    i = 1;
    for k = 1 : N
        for j = 1 : frameSize
            if(i > SIZE)
                break;
            end
            fr(k, j) = A(i);
            i = i + 1;
        end
        i = i - overLap;
    end
end