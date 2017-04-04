int tot, rt[N], sum[N * 20], ls[N * 20], rs[N * 20];
void build(int &t, int l, int r) {
	if (t == 0) {
		t = ++tot;
		sum[t] = ls[t] = rs[t] = 0;
	}
	if (l < r) {
		int mid = (l + r) >> 1;
		build(ls[t], l, mid), build(rs[t], mid + 1, r);
	}
}
void ins(int &t, int e, int l, int r, int p) {
	t = ++tot;
	sum[t] = ls[t] = rs[t] = 0;
	if (l >= r) {
		sum[t] = sum[e];
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) {
		rs[t] = rs[e];
		ins(ls[t], ls[e], l, mid, p);
	} else {
		ls[t] = ls[e];
		ins(rs[t], rs[e], mid + 1, r, p);
	}
	sum[t] = sum[ls[t]] + sum[rs[t]];
}
void upd(int t, int l, int r, int p, int v) {
	if (l == r) {
		sum[t] += v;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid)
		upd(ls[t], l, mid, p, v);
	else
		upd(rs[t], mid + 1, r, p, v);
	sum[t] = sum[ls[t]] + sum[rs[t]];
}
int qry(int t, int l, int r, int L, int R) {
	if (L <= l && r <= R)
		return sum[t];
	int mid = (l + r) >> 1;
	if (R <= mid)
		return qry(ls[t], l, mid, L, R);
	if (L > mid)
		return qry(rs[t], mid + 1, r, L, R);
	return qry(ls[t], l, mid, L, R) + qry(rs[t], mid + 1, r, L, R);
}
