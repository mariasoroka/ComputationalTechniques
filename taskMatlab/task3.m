%https://www.mathworks.com/help/stats/prob.normaldistribution.random.html?searchHighlight=random&s_tid=srchtitle
%%
clc
%%
rng(0);
r_norm = random('Normal', 0, 1, 1, 100);
r_lognorm = random('Lognormal', 2, 0, 1, 100);
r_exp = random('Exponential', 4, 1, 100);
r_chisq = random('Chisquare', 4, 1, 100);
%disp(r_norm);
%disp(r_lognorm);
%disp(r_exp);
%disp(r_chisq);
%%
[f_str, x_str] = ecdf(r_norm);
CDF_str = cdf('Normal', x_str, 0, 1);

subplot(2, 1, 1);
plot(x_str, CDF_str, 'b');
title("Exact");

subplot(2, 1, 2);
stairs(x_str, f_str, 'g');
title("Emperical");
%%
my_hist(r_norm);
%%
PDF_str = pdf('Normal', x_str, 0, 1);
plot(x_str, PDF_str, 'b');

%%
close all;
y = rand(5);
p = plot(y);
%%
c = get(p(1), 'Color');
disp(c);
%%
set(p(1), 'LineStyle', '--');
%%
h = findobj('LineStyle', '--')
set(h, 'LineWidth', 2);
%%
function my_hist(X)
    h = histogram(X,'Normalization','pdf');
    h.NumBins = 50;
end