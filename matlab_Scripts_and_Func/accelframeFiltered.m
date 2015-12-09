obsV3 = zeros(N, 2, 3);
for ax = 1 : 3
    %figure
    %plot(dn(:, ax))
    [frames, N] = getFilteredFrames(dn(:,ax), 6, 30, 8, 0.1);
    
    %figure;

    for i = 1 : N
        %subplot(4, 2, i); 
        %plot(frames(i,:));
        [obsV3(i, 1, ax), obsV3(i, 2, ax)] = obsVec(frames(i, :));
    end
end