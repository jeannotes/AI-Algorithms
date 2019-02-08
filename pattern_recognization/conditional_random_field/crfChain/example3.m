% Generate some data
nInstances = 250;
nVars = 50;
X = randn(nInstances,nVars);
y = X*((rand(nVars,1) > .5).*randn(nVars,1)) + randn(nInstances,1);

% Least Squares Solution
wLS = X\y;

% Ridge Regression
lambda = 100*ones(nVars,1); % Penalize each element by the same amount
R = chol(X'*X + diag(lambda));
wRR = R\(R'\(X'*y));

% LASSO
lambda = 100*ones(nVars,1); % Penalize the absolute value of each element by the same amount
funObj = @(w)SquaredError(w,X,y); % Loss function that L1 regularization is applied to
w_init = wRR; % Initial value for iterative optimizer
fprintf('\nComputing LASSO Coefficients...\n');
wLASSO = L1General2_PSSgb(funObj,w_init,lambda);

fprintf('Number of non-zero variables in Least Squares solution: %d\n',nnz(wLS));
fprintf('Number of non-zero variables in Ridge Regression solution: %d\n',nnz(wRR));
fprintf('Number of non-zero variables in LASSO solution: %d\n',nnz(wLASSO));

figure;
clf;hold on;
subplot(2,2,1);
stem(wLS,'r');
xlim([1 nVars]);
yl = ylim;
title('Least Squares');
subplot(2,2,2);
stem(wRR,'b');
xlim([1 nVars]);
ylim(yl);
title('Ridge Regression');
subplot(2,2,3);
stem(wLASSO,'g');
xlim([1 nVars]);
title('LASSO');
ylim(yl);
pause;