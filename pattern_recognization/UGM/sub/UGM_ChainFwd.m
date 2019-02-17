function [alpha,kappa,mxState] = UGM_ChainFwd(nodePot,edgePot,nStates,maximize)
[nNodes,maxState] = size(nodePot);

alpha = zeros(nNodes,maxState);
alpha(1,1:nStates(1)) = nodePot(1,1:nStates(1));
kappa(1) = sum(alpha(1,1:nStates(1)));
alpha(1,1:nStates(1)) = alpha(1,1:nStates(1))/kappa(1);
for n = 2:nNodes
   tmp = repmat(alpha(n-1,1:nStates(n-1))',1,nStates(n)).*edgePot(1:nStates(n-1),1:nStates(n),n-1); 
   if maximize
      alpha(n,1:nStates(n)) = nodePot(n,1:nStates(n)).*max(tmp);
      %{
[Y,I] = max(X) returns the indices of the maximum values in vector I.      
a =
     2     8     4
     7     3     9
     1    10     5
[c d] = max(a)
c =
     7    10     9
d =
     2     3     2
      so in mxState, we get the indices
      %}
      [mxPot mxState(n,1:nStates(n))] = max(tmp);
   else
       alpha(n,1:nStates(n)) = nodePot(n,1:nStates(n)).*sum(tmp);
       % here, referenc to crfchain, just another crf-lib
   end
   
   % Normalize Message
   kappa(n) = sum(alpha(n,1:nStates(n)));
   alpha(n,1:nStates(n)) = alpha(n,1:nStates(n))/kappa(n);
end
%{
actually vitebi algorithm
in mxState, we store every node's best candidate(namely state1, state2, state3....)
abd this is psai in P185, chapter 10, hmm, but also apply in this chapter
so psai(i) records last time's best state
%}