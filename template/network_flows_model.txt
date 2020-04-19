无源汇上下界最大流
define 
	virtual source S, virtual sink T
construct 
	du[i] = must_in[i] - must_out[i]
	addEdge(S, i, cap = du[i]) if du[i] > 0	
	addEdge(i, T, cap = -du[i]) if du[i] < 0
result
	if maxflow(S, T) == sum(du[i]) with du[i] > 0
	then exist a feasible solution.

有源汇上下界最大流
define
	source S, sink T, virtual source SS, virtual sink TT	
construct
	addEdge(T, S, cap = INF)	
	(the remaining steps are the same as 无源汇上下界最大流)		
result
	1. there must be a feasible solution from SS to TT.
	2. answer = maxflow(SS, TT)	+ maxflow(S, T) // don't chnage order

有源汇上下界最小流
define 
	source S, sink T, virtual source SS, virtual sink TT
construct
	(first, view problem as 无源汇上下界最大流)
	addEdge(T, S, cap = INF) after get maxflow(SS, TT)	
result
	1. get maxflow(SS, TT)
	2. addEdge(T, S, cap = INF)
	3. get maxflow(SS, TT) again
	4. if all S->i are full, there exits a solution and the answer 
	   equals to flow(S, T) now
		
最大权闭合子图
define
	source S, sink T	
construct
	addEdge(S, i, cap = weight[i]) if weight[i] > 0
	addEdge(i, T, cap = -weight[i]) if weight[i] < 0	
result
	answer = sum(weight[i] > 0) with weight[i] > 0 - maxflow(S, T)
