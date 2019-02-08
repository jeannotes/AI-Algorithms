clear all
useMex = 0; % Set this to 1 to use mex files to speed things up

%% Generate Synthetic Data

% Notes:
%   - X is categorical, each element X(i,j) contains the value of feature j for word i,
%       a value of '0' means ignore the feature for this training example
%   - y is cateogircal, each element y(i) contains the label for word i
%       a value of '0' indicates the position between sentences
[X,y] = crfChain_genSynthetic;

nWords = size(X,1);
nWords % 1000
nStates = max(y);
nStates % 4
nFeatures = max(X);
nFeatures 
%% Initialize parameters and data structures

[w,v_start,v_end,v] = crfChain_initWeights(nFeatures,nStates,'randn');
featureStart = cumsum([1 nFeatures(1:end)]); % data structure which relates high-level 'features' to elements of w
sentences = crfChain_initSentences(y);
nSentences = size(sentences,1);

wv = [w(:);v_start(:);v_end(:);v(:)];

%% Set up training/testing indices
trainNdx = 1:floor(nSentences/2);
testNdx = floor(nSentences/2)+1:nSentences;

%% Example of making potentials and doing inference with first sentence

s = 1;
if useMex
    [nodePot,edgePot] = crfChain_makePotentialsC(X,wv,nFeatures,featureStart,sentences,s,nStates);
    [nodeBel,edgeBel,logZ] = crfChain_inferC(nodePot,edgePot);
else
    [nodePot,edgePot]=crfChain_makePotentials(X,w,v_start,v_end,v,nFeatures,featureStart,sentences,s);
    [nodeBel,edgeBel,logZ] = crfChain_infer(nodePot,edgePot);
end

%% Compute Errors with random parameters

% fprintf('Errors based on most likely sequence with random parameters:\n');

trainErr = crfChain_error(w,v_start,v_end,v,X,y,nStates,nFeatures,featureStart,sentences(trainNdx,:),'decode',useMex);
testErr = crfChain_error(w,v_start,v_end,v,X,y,nStates,nFeatures,featureStart,sentences(testNdx,:),'decode',useMex);

% fprintf('Errors based on max marginals with random parameters:\n');

trainErr = crfChain_error(w,v_start,v_end,v,X,y,nStates,nFeatures,featureStart,sentences(trainNdx,:),'infer',useMex);
testErr = crfChain_error(w,v_start,v_end,v,X,y,nStates,nFeatures,featureStart,sentences(testNdx,:),'infer',useMex);