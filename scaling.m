close all
clear all

ms = 6;
lw = 1;
fs = 16;

chameleongreen2 = [188,225,141] / 255;
chameleongreen3 = [ 51,149, 48] / 255;
chameleongreen4 = [  0, 98, 90] / 255;

ex = [ ...
    experiment('vexcl_1gpu',     'VexCL (1 GPU)',  'k--',  'w', ms, lw) ...
    experiment('vexcl_2gpu',     'VexCL (2 GPUs)', 'ko-', 'w', ms, lw) ...
    experiment('vexcl_3gpu',     'VexCL (3 GPUs)', 'ko-', 'w', ms, lw) ...
    ];

figure(1)
set(gca, 'FontSize', fs);

h = zeros(1, length(ex));

for i = 1:length(ex)
    if i == 1 || i == 4
	ref = ex(i).t;
    end

    h(i) = ex(i).semilogx(ref ./ ex(i).t);
    hold on
end

pacificorange = rgb2cmyk([0.15, 0.45, 1.00, 0.00]);

set(h(1), 'color', chameleongreen4, 'markerfacecolor', chameleongreen4);
set(h(2), 'color', chameleongreen2, 'markerfacecolor', chameleongreen2);
set(h(3), 'color', chameleongreen3, 'markerfacecolor', chameleongreen3);

xlim([1e2 1e7])
ylim([0 3])
set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
xlabel('N');
ylabel('T(1 GPU) / T');
legend(ex(:).legend, 'location', 'NorthWest');
legend boxoff
axis square

print('-depsc', 'scaling.eps');
