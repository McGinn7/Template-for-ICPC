bool used[N];
double x[N], a[N][N];
int gauss(int n, int m) {
	int row, col;
	for (row = col = 0; row < n && col < m; ++row, ++col) {
		int mxr = row;
		rep(i, row + 1, n)
			if (fabs(a[i][col]) > fabs(a[mxr][col]))
				mxr = i;
		if (fabs(a[mxr][col]) < EPS) {
			--row;
			continue;
		}
		if (mxr != row)
			swap(a[row], a[mxr]);
		rep(i, 0, n)
			if (i != row && fabs(a[i][col]) > EPS)
				for (int j = m; j >= col; --j)
					a[i][j] -= a[row][j] * a[i][col] / a[row][col];
	}
	if (row == n && n == m) {
		rep(i, 0, n)
			x[i] = a[i][m] / a[i][i];
//		rep(i, 0, n)
//			printf("x[%d] = %lf\n", i, x[i]);
		return 1;
	}
	rep(i, row + 1, n)
		if (a[i][m] > EPS)
			return -1; // No Solution
	return 0;
	// free_num = m - row
	memset(used, false, sizeof(used[0]) * m);
	rep(i, 0, row)
	{
		int cnt = 0, ind = -1;
		rep(j, 0, m)
			if (fabs(a[i][j]) > EPS && !used[j])
				++cnt, ind = j;
		if (cnt == 1)
			x[ind] = a[i][m] / a[i][ind], used[ind] = true;
	}
//	rep(i, 0, m)
//		if (used[i])
//			printf("x[%d] = %lf\n", i, x[i] + EPS);
//		else
//			printf("x[%d] = not determined\n", i);
}
