% minFunc
fprintf('Compiling minFunc files...\n');
mex minFunc/lbfgsC.c

% KPM
fprintf('Compiling KPM files...\n');
mex -IKPM KPM/repmatC.c

% crfChain
fprintf('Compiling crfChain files...\n');
mex crfChain/mex/crfChain_makePotentialsC.c
mex crfChain/mex/crfChain_inferC.c
mex crfChain/mex/crfChain_lossC2.c