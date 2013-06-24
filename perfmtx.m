close all
clear all

pacificorange = rgb2cmyk([0.15, 0.45, 1.00, 0.00]);
pacificgray   = rgb2cmyk([0.00, 0.15, 0.35, 0.60]);
pacificlgray  = rgb2cmyk([0.00, 0.00, 0.20, 0.40]);
pacificcream  = rgb2cmyk([0.05, 0.05, 0.15, 0.00]);
deepyellow    = rgb2cmyk([0.00, 0.17, 0.80, 0.00]);
lightblue     = rgb2cmyk([0.49, 0.01, 0.00, 0.00]);
lightbrown    = rgb2cmyk([0.09, 0.15, 0.34, 0.00]);
deepviolet    = rgb2cmyk([0.79, 1.00, 0.00, 0.15]);
deeporange    = rgb2cmyk([0.00, 0.59, 1.00, 0.18]);
dustyred      = rgb2cmyk([0.00, 0.70, 0.45, 0.40]);
grassgreen    = [92/255,135/255,39/255];
pacificblue   = [59/255,110/255,143/255];
pacificgreen  = rgb2cmyk([0.15, 0.00, 0.45, 0.30]);
deepblue      = rgb2cmyk([1.00, 0.57, 0.00, 0.20]);
turquoise     = rgb2cmyk([0.43, 0.00, 0.24, 0.00]);

figure(1)
set(gcf, 'position', [50, 50, 1000, 500]);

ms = 3;
lw = 0.75;
fs = 10;

ex = [ ...
    experiment('thrust_gpu',     'Thrust GPU',	     'ko-', 'k', ms, lw) ...
    experiment('thrust_cpu',     'Thrust CPU',	     'ko-', 'w', ms, lw) ...
    experiment('vexcl_1gpu',     'VexCL GPU',        'ro-', 'r', ms, lw) ...
    experiment('vexcl_cpu',      'VexCL CPU',        'ro-', 'w', ms, lw) ...
    experiment('custom_1gpu',    'Custom Kernel',    'bo-', 'b', ms, lw) ...
    experiment('generated_1gpu', 'Generated Kernel', 'ro-', 'r', ms, lw) ...
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
    h2(i) = ex(i).loglog(ex(i).t ./ ref);
    hold on
end

set(h1(3), 'color', pacificorange, 'markerfacecolor', pacificorange);
set(h2(3), 'color', pacificorange, 'markerfacecolor', pacificorange);
set(h1(4), 'color', pacificorange);
set(h2(4), 'color', pacificorange);
set(h1(5), 'color', grassgreen, 'markerfacecolor', grassgreen);
set(h2(5), 'color', grassgreen, 'markerfacecolor', grassgreen);

subplot(1, 2, 1);
xlim([1e2 1e7])
set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
xlabel('N');
ylabel('T (sec)');
h = legend(ex(:).legend, 'location', 'NorthWest');
set(h, 'fontsize', 8);
legend boxoff
axis square

subplot(1, 2, 2);
plot([1e4 1e4], [1e-2, 1e2], 'k:');
xlim([1e2 1e7])
set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
xlabel('N');
ylabel('T / T(Thrust GPU)');
axis square

print('-depsc', 'perfcmp.eps');
