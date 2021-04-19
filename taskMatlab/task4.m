%% 1
rng(0)
n_norm = 2000;
n_even_per_norm = 10000;
n_even = n_norm * n_even_per_norm;
even = rand(1, n_even);
norm = zeros(1, n_norm);
for i=1:n_norm
    norm(i) = sum(even((i - 1) * n_even_per_norm + 1 : (i) * n_even_per_norm));
end 
norm = norm - n_even_per_norm * 0.5;
norm = norm / sqrt(n_even_per_norm / 12);
disp(norm);
h = histogram(norm,'Normalization','pdf');
h.NumBins = 50;
%% 2.1
rng(0)
n = 200;
even = rand(1, n);
exp = zeros(1, n);
lambda = 2;
for i = 1:n
    if even(i) ~= 1
        exp(i) = - 1 / lambda * log(1 - even(i));
    end
end
disp(exp);
h = histogram(exp,'Normalization','pdf');
h.NumBins = 50;
%% 2.2
clear;
rng(0);
n = 1000;
even = rand(1, n);
a = 0;
sigma = 1;
disp(tan((even-0.5) * pi) + a);
cauchy = (sigma * tan((even - 0.5) * pi)) + a;
%disp(cauchy);
h = histogram(cauchy,'Normalization','pdf', 'BinLimits', [-10, 10]);
h.NumBins = 100;
%% 3.1
rng(0)
k = 3;
n = 1000;
norm_str = randn(k, n);
chi_squared = sum(norm_str .^ 2, 1);
disp(chi_squared);
h = histogram(chi_squared,'Normalization','pdf');
h.NumBins = 100;
%% 3.2
rng(0)
n = 1000;
norm_str = randn(2, n)
cauchy = norm_str(1, :) ./ norm_str(2, :);
disp(cauchy);
h = histogram(cauchy,'Normalization','pdf', 'BinLimits', [-10, 10]);
h.NumBins = 100;
%% 4
rng(0);
n = 10000;
num_fin = 0;
uniform = random('Uniform', -1, 1, 2, n); 
norm_1 = zeros(1, n);
norm_2 = zeros(1, n);
for i = 1:n
    R = uniform(1, i) ^ 2 + uniform(2, i) ^ 2;
    if R <= 1
        num_fin = num_fin + 1;
        norm_1(num_fin) = uniform(1, i) * sqrt(-2 * log(R) / R);
        norm_2(num_fin) = uniform(2, i) * sqrt(-2 * log(R) / R);
    end
end
disp(norm_1(1:num_fin));
D = corrcoef(norm_1, norm_2);
disp(D);
h = histogram(norm_1(1:num_fin), 'Normalization','pdf');
h.NumBins = 100;
hold on
h = histogram(norm_2(1:num_fin), 'Normalization','pdf');
h.NumBins = 100;