struct Node {
	int x, y;
	Node() {
		x = y = 0;
	}
	Node(int _x, int _y) {
		x = _x, y = _y;
	}
	void in() {
		scanf("%d%d", &x, &y);
	}
	Node operator-(const Node &p) const {
		return Node(x - p.x, y - p.y);
	}
	int operator^(const Node &p) const {
		return x * p.y - y * p.x;
	}
} p[N];
int n, m;
bool cmp(const Node &p, const Node &q) {
	if (p.x != q.x)
		return p.x < q.x;
	return p.y < q.y;
}
int mid, top, s[N];
int convex(int l, int r) {
	top = 0;
	for (int i = l; i <= r; s[++top] = i++)
		while (top > 1
				&& ((p[s[top]] - p[s[top - 1]]) ^ (p[i] - p[s[top - 1]])) < 0)
			--top;
	mid = top;
	for (int i = r - 1; i >= l; s[++top] = i--)
		while (top > mid
				&& ((p[s[top]] - p[s[top - 1]]) ^ (p[i] - p[s[top - 1]])) < 0)
			--top;
	return top - 1;
}
ll area() {
	ll ret = 0;
	rep(i, 1, n)
		ret += abs((p[i] - p[0]) ^ (p[i - 1] - p[0]));
	return ret;
}
