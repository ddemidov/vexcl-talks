close all
clear all

figure(1)
set(gcf, 'position', [50, 50, 1000, 500]);

ms = 3;
lw = 0.75;
fs = 10;

ex = [ ...
    experiment('vexcl_cpu',      'Naive (CPU)',  'ko-', 'w', ms, lw) ...
    experiment('generated_cpu',  'Generated (CPU)','ko-', 'k', ms, lw) ...
    experiment('vexcl_1gpu',     'Naive (GPU)',        'ro-', 'w', ms, lw) ...
    experiment('generated_1gpu', 'Generated (GPU)',    'ro-', 'w', ms, lw) ...
    ];

subplot(1, 2, 1); set(gca, 'FontSize', fs);
subplot(1, 2, 2); set(gca, 'FontSize', fs);

h1 = zeros(1,length(ex));
h2 = zeros(1,length(ex));

ref = ex(3).t;

for i = 1:length(ex)
    subplot(1, 2, 1);
    h1(i) = ex(i).loglog();
    hold on

    subplot(1, 2, 2);
    h2(i) = ex(i).loglog(ex(i).t ./ ref);
    hold on
end

set(h1(3), 'color', chameleon(3));
set(h2(3), 'color', chameleon(3));
set(h1(4), 'color', chameleon(3), 'markerfacecolor', chameleon(3));
set(h2(4), 'color', chameleon(3), 'markerfacecolor', chameleon(3));

subplot(1, 2, 1);
xlim([1e2 1e7])
set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
xlabel('Problem size');
ylabel('T (sec)');
h = legend(ex(:).legend, 'location', 'NorthWest');
legend boxoff
axis square

subplot(1, 2, 2);
plot([1e4 1e4], [1e-2, 1e2], 'k:');
xlim([1e2 1e7])
set(gca, 'xtick', [1e2 1e3 1e4 1e5 1e6 1e7])
xlabel('Problem size');
ylabel('T / T(Naive GPU)');
axis square

print('-depsc', 'perfgen.eps');
