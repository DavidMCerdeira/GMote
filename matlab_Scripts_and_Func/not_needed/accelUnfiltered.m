figure
plot(dn(:, 1))
[frames, N] = getFrames(dn(:,1), 6, 30);
obsV1 = zeros(N, 2);
figure;

for i = 1 : N
    subplot(4, 2, i); 
    plot(frames(i,:));
    [obsV1(i, 1), obsV1(i,2)] = obsVec(frames(i, :));
end