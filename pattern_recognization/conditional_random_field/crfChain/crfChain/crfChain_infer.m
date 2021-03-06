function [nodeBel,edgeBel,logZ] = crfChian_infer(nodePot,edgePot)

[nNodes,nStates] = size(nodePot);

% Forward Pass
alpha = zeros(nNodes,nStates);
alpha(1,:) = nodePot(1,:);
Z(1) = sum(alpha(1,:));
alpha(1,:) = alpha(1,:)/Z(1);
for n = 2:nNodes % Forward Pass
    tmp = repmatC(alpha(n-1,:)',1,nStates).*edgePot;
    % this actually computes another part summing, which is transition
    % probability
    %{
  in all this is equall to:
    
  alpha * [ sig(node_1.*edge_1) sig(node_2.*edge_2) sig(node_3.*edge_3).... sig(node_n.*edge_n)  ]
    sig means sum
    
    %}
    alpha(n,:) = nodePot(n,:).*sum(tmp);
    % Normalize
    Z(n) = sum(alpha(n,:));
    alpha(n,:) = alpha(n,:)/Z(n);
end

% Backward Pass
beta = zeros(nNodes,nStates);
beta(nNodes,:) = 1;
for n = nNodes-1:-1:1 % Backward Pass
    tmp = repmatC(nodePot(n+1,:),nStates,1).*edgePot;
    tmp2 = repmatC(beta(n+1,:),nStates,1);
    beta(n,:) = sum(tmp.*tmp2,2)';
    
    % Normalize
    beta(n,:) = beta(n,:)/sum(beta(n,:));
end

% Compute Node Beliefs p209 (11.32)
nodeBel = zeros(size(nodePot));
for n = 1:nNodes
    tmp = alpha(n,:).*beta(n,:);
    nodeBel(n,:) = tmp/sum(tmp);
end

% Compute Edge Beliefs p209 (11.33)
edgeBel = zeros(nStates,nStates,nNodes-1);
for n = 1:nNodes-1
    tmp = zeros(nStates);
    for i = 1:nStates
        for j = 1:nStates
            tmp(i,j) = alpha(n,i)*nodePot(n+1,j)*beta(n+1,j)*edgePot(i,j);
        end
    end
    edgeBel(:,:,n) = tmp./sum(tmp(:));
end
% Compute logZ
logZ = sum(log(Z));