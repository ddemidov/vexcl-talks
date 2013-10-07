x = rand(10,1);
y = rand(10,1);
z = peaks(x,y);

f = fopen('peaks.dat', 'w');
for i = 1:length(x)
    fprintf(f, '%f %f %f\n', x(i), y(i), z(i));
end

fclose(f)
