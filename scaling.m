close all
clear all

ms = 6;
lw = 1;
fs = 16;

ex = [ ...
    experiment('vexcl_1gpu',     'VexCL (1 GPU)',  'k:',  'w', ms, lw) ...
    experiment('vexcl_2gpu',     'VexCL (2 GPU)',  'ko-', 'k', ms, lw) ...
    experiment('vexcl_3gpu',     'VexCL (3 GPU)',  'ko-', 'w', ms, lw) ...
    experiment('generated_1gpu', 'Gen. kernel (1 GPU)', 'k:',  'w', ms, lw) ...
    experiment('generated_2gpu', 'Gen. kernel (2 GPU)', 'ro-', 'r', ms, lw) ...
    experiment('generated_3gpu', 'Gen. kernel (3 GPU)', 'ro-', 'w', ms, lw) ...
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

set(h(5), 'color', pacificorange, 'markerfacecolor', pacificorange);
set(h(6), 'color', pacificorange);

xlim([1e2 1e7])
ylim([0 3])
set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
xlabel('N');
ylabel('T(1 GPU) / T');
legend(ex(:).legend, 'location', 'NorthWest');
legend boxoff
axis square

print('-depsc', 'scaling.eps');
