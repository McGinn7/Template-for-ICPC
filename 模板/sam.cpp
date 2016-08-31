struct Node {
	static const int M = 27;
	int mxl;
	Node *pre, *go[M];
	void clear() {
		mxl = 0, pre = 0;
		memset(go, 0, sizeof(go));
	}
}*root, *last, *cur, pool[N << 1];
void init() {
	cur = pool;
	root = last = cur++;
	root->clear();
}
void insert(int x) {
	Node *p = last, *np = cur++;
	np->clear();
	np->mxl = p->mxl + 1;
	while (p && !p->go[x])
		p->go[x] = np, p = p->pre;
	if (!p) {
		np->pre = root;
	} else {
		Node *q = p->go[x];
		if (q->mxl == p->mxl + 1) {
			np->pre = q;
		} else {
			Node *nq = cur++;
			nq->clear();
			nq->pre = q->pre, nq->mxl = p->mxl + 1;
			memcpy(nq->go, q->go, sizeof(nq->go));
			np->pre = q->pre = nq;
			while (p && p->go[x] == q)
				p->go[x] = nq, p = p->pre;
		}
	}
	last = np;
}