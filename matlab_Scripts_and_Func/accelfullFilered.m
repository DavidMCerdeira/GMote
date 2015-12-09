%caso 2
figure
lp = fir1(29, 0.1);
dnf = filter(lp, 1, dn);
plot(dnf(:,1));
i = 1;

[frames, N] = getFrames(dnf, 6, 30);
obsV2 = zeros(N, 2);
figure;

for i = 1 : N
    subplot(4, 2, i); 
    plot(frames(i,:));
    [obsV2(i, 1), obsV2(i,2)] = obsVec(frames(i, :));
end