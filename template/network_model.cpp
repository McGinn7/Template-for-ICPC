/*
	无源汇上下界最大流
	du[i] = in[i] - out[i]
	du[i] > 0, add edge S -> i(cap = du[i])
	du[i] < 0, add edge i -> T(cap = -du[i])
	if maxflow(S, T) = sum{du[i]}, du[i] > 0, 
	exist a feasible solution.

	有源汇上下界最大流
	source S, sink T, super source SS, super sink TT
	add edge T -> S(cap = INF), change to 无源汇网络流
	1. get flow1 = maxflow(SS, TT)
	2. if exist a feasible solution, get flow2 = maxflow(S, T)
	answer = flow1 + flow2

	有源汇上下界最小流
	source S, sink T, super source SS, super sink TT
	1. get maxflow(SS, TT)
	2. add edge T -> S(cap = INF)
	3. get maxflow(SS, TT)
	if all flow of edge S->i equal to 0, exist solution and
		the answer = flow[S->T]

	最大权闭合子图
	weight[v] > 0, add edge S -> v(cap = weight[v])
	weight[v] < 0, add edge v -> T(cap = -weight[v])
	answer = sum(weight[v]) - maxflow(S, T), weight[v] > 0
*/
