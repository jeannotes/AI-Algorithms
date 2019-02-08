function [w,v_start,v_end,v] = crfChain_initWeights(nFeatures,nStates,type)
% nFeatures
% nStates
% type
if strcmp(type,'zeros')
    initFunc = @zeros;
else
    initFunc = @randn;
end
v_start = initFunc(nStates,1); % potential for tags to start sentences
% v_start
v = initFunc(nStates,nStates); % potentials for transitions between tags
% v
v_end = initFunc(nStates,1); % potential for tags to end sentences
% v_end
fprintf('crfChain_initWeights nFeatures')
nFeatures
w = initFunc(sum(nFeatures)*nStates,1); % potential of tag given individual features
