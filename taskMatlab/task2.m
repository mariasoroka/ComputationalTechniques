clc
%%
RandStream.list
%%
s1 = RandStream.create('mrg32k3a','NumStreams',1,'Seed',0,'StreamIndices',1);
%s2 = RandStream.create('mrg32k3a','NumStreams',5,'Seed', 1,'StreamIndices',2);
%%
r1 = rand(s1,100000,1); 
r2 = rand(s2,100000,1); 
corrcoef([r1,r2])
%%
r1 = rand(s1, 1, 10);
disp(r1);
%%
r2 = rand(s1, 1, 10);
disp(r2);
disp(r1-r2);
%%
reset(s1, 0)
%%
r2 = rand(s1, 1, 10);
disp(r2);
disp(r1-r2);
%%
randi1 = randi(200, 1, 10);
randi2 = randi(200, 1, 10);
disp(randi1 - randi2);
%%
rng(0)
randi2 = randi(200, 1, 10);
disp(randi1 - randi2);
%%
randn1 = randn(1, 10);
randn2 = randn(1, 10);
disp(randn1 - randn2);
%%
rng(0)
%%
randn2 = randn(1, 10);
disp(randn1 - randn2);
%'NormalTransform' — Normal transformation algorithm
%'Ziggurat' | 'Polar' | 'Inversion'
%%

