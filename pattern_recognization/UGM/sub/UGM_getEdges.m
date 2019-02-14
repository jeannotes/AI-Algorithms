function [edges] = UGM_getEdges(n,edgeStruct)
edges = edgeStruct.E(edgeStruct.V(n):edgeStruct.V(n+1)-1);
%{
e=[
    [indexes of edges connected to node 1], [1]  , v[1]=1
    [indexes of edges connected to node 2], [1 2], v[2]=2
    [indexes of edges connected to node 3]  [2,3], v[3]=4   ....
    ]
these [indexes of edges ..] is not single one, now we enumerate them
together
%}