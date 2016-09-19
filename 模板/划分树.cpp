int arr[N], ln[20][N], val[20][N];
void build(int d, int l, int r) {
	if (l >= r)
		return;
	int mid = (l + r) >> 1, L = l, R = mid + 1, same = mid - l + 1;
	rep(i, l, r + 1)
		same -= val[d][i] < arr[mid];
	rep(i, l, r + 1)
	{
		int flag = 0;
		if (val[d][i] < arr[mid] || (val[d][i] == arr[mid] && same)) {
			flag = 1;
			same -= val[d][i] == arr[mid];
			val[d + 1][L++] = val[d][i];
		} else {
			val[d + 1][R++] = val[d][i];
		}
		ln[d][i] = ln[d][i - 1] + flag;
	}
	build(d + 1, l, mid), build(d + 1, mid + 1, r);
}
int query(int d, int l, int r, int L, int R, int k) {
	if (l >= r)
		return val[d][l];
	int mid = (l + r) >> 1, pl, pr;
	pl = ln[d][L - 1] - ln[d][l - 1], pr = ln[d][R] - ln[d][l - 1];
	if (k <= ln[d][R] - ln[d][L - 1]) {
		return query(d + 1, l, mid, l + pl, l + pr - 1, k);
	} else {
		pl = L - l - pl, pr = R - l + 1 - pr;
		return query(d + 1, mid + 1, r, mid + 1 + pl, mid + 1 + pr - 1,
				k - (ln[d][R] - ln[d][L - 1]));
	}
}
void init() {
	rep(i, 1, n + 1)
		val[0][i] = arr[i];
	rep(i, 0, 20)
		ln[i][0] = 0;
	sort(arr + 1, arr + 1 + n);
	build(0, 1, n);
}
