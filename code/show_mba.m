close all
clear all

chameleon1 = [  0,  48,  87] / 255;
chameleon2 = [217, 200, 158] / 255;
chameleon3 = [242, 169,   0] / 255;
chameleon4 = [203,  96,  21] / 255;

p = load('peaks.dat');
c = load('c.dat');

x = linspace(0, 1, 20);
y = linspace(0, 1, 20);

[X, Y] = meshgrid(x, y);
h = mesh(X, Y, c);
set(h, 'linewidth', 1)
hold on
scatter3(p(:,1), p(:,2), p(:,3), 30, 'k', 'filled');

cmap = zeros(255,3);
for i=0:255
    cmap(i+1,:) = i/255*chameleon3 + (255 - i)/255*chameleon4;
end
colormap(cmap)

set(gca, 'xticklabel', [])
set(gca, 'yticklabel', [])
set(gca, 'zticklabel', [])

axis square

print('-depsc', 'mba.eps')
