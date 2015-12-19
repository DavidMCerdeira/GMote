function [ffr, N] = getFilteredFrames(A, overlap, frameSize, O, Wn)
    [fr, N] = getFrames(A, overlap, frameSize);
    lp = fir1(O, Wn);
    ffr = zeros(N, frameSize);
    
    for i = 1 : N
        ffr(i,:) = filter(lp, 1, fr(i,:));
    end
end