close all
clear all

chameleon1 = [  0,  48,  87] / 255;
chameleon2 = [217, 200, 158] / 255 * 0.75;
chameleon3 = [242, 169,   0] / 255;
chameleon4 = [203,  96,  21] / 255;

figure(1)
set(gcf, 'position', [50, 50, 1000, 500]);

ms = 3;
lw = 0.75;
fs = 10;

ex = [ ...
    experiment('cublas',          'CUBLAS', 'o-', chameleon1, ms, lw) ...
    experiment('vexcl_naive',     'VexCL',  'o-', chameleon3, ms, lw) ...
    experiment('thrust',          'Thrust', 'o-', chameleon2, ms, lw) ...
    ];

subplot(1, 2, 1); set(gca, 'FontSize', fs);
subplot(1, 2, 2); set(gca, 'FontSize', fs);

h1 = zeros(1,length(ex));
h2 = zeros(1,length(ex));

for i = 1:length(ex)
    if i == 1
	ref = ex(i).t;
    end

    subplot(1, 2, 1);
    h1(i) = ex(i).loglog();
    hold on

    subplot(1, 2, 2);
    h2(i) = ex(i).semilogx(ref ./ ex(i).t);
    hold on

    subplot(1, 2, 1);
    xlim([1e2 1e7])
    ylim([1e-1 1e3])
    set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
    xlabel('N');
    ylabel('T (sec)');
    h = legend(ex(1:i).legend, 'location', 'NorthWest');
    set(h, 'fontsize', 12);
    legend boxoff
    axis square

    subplot(1, 2, 2);
    xlim([1e2 1e7])
    ylim([0.5 2.5])
    set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
    xlabel('N');
    ylabel(['T(' ex(1).legend ') / T']);
    axis square

    print('-depsc', ['perfcmp-' num2str(i) '.eps']);
end
