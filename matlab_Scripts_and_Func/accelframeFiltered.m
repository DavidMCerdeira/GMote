figure
plot(dn(:, 1))
[frames, N] = getFilteredFrames(dn(:,1), 6, 30, 8, 0.1);
obsV3 = zeros(N, 2);
figure;

for i = 1 : N
    subplot(4, 2, i); 
    plot(frames(i,:));
    [obsV3(i, 1), obsV3(i,2)] = obsVec(frames(i, :));
end