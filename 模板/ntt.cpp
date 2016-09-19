void change(int *x, int len) {
	int i, j, k;
	for (i = 1, j = len >> 1; i < len - 1; ++i) {
		if (i < j)
			swap(x[i], x[j]);
		k = len >> 1;
		while (j >= k)
			j -= k, k >>= 1;
		if (j < k)
			j += k;
	}
}
const int G = 3;
void ntt(int *x, int len, int rev) {
	change(x, len);
	int id = 0;
	for (int h = 2; h <= len; h <<= 1) {
		++id;
		int wn = kpow(G, (MOD - 1) / (1 << id));
		for (int j = 0; j < len; j += h) {
			int w = 1;
			for (int k = j; k < j + h / 2; ++k) {
				int u = x[k] % MOD, t = 1ll * w * x[k + h / 2] % MOD;
				x[k] = (u + t) % MOD;
				x[k + h / 2] = ((u - t) % MOD + MOD) % MOD;
				w = 1ll * w * wn % MOD;
			}
		}
	}
	if (rev == -1) {
		for (int i = 1; i < len / 2; ++i)
			swap(x[i], x[len - i]);
		int inv = kpow(len, MOD - 2);
		for (int i = 0; i < len; ++i)
			x[i] = 1ll * x[i] * inv % MOD;
	}
}
int A[N * 4], B[N * 4];
