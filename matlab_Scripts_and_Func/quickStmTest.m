instrreset
s = serial('COM3', 'BaudRate', 2000000, 'Timeout', 1000);
fopen(s);
d = 0;

stm = [];
while d ~= -1
    d = fscanf(s, '%d\n');
    if(d ~= -1)
        stm = [stm; d];
    end
end

fclose(s);
for i = 1 : 7
    fprintf('%10s(%d) %6.2f\n', h{i}.name, i-1, h{i}.problem1(stm+1))
end