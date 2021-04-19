
%%
plot(Gen(60, 5, 3, 16, 7))
%период 16
%%
plot(Gen(60, 5, 3, 32, 7))
%период 32
%%
plot(Gen(60, 7 ^ 5, 3, 2 ^ 31 - 1, 14))
%%
function res = Gen(n, a, c, m, z_0)
    res = zeros(1, n);
    res(1) = z_0;
    for i = 2:n
        res(i) = mod(res(i - 1) * a + c, m);
    end
end