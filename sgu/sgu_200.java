import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Solution {

	static int t, m;
	static int[] pri;
	static int[][] a;

	static BigInteger val(int value) {
		return BigInteger.valueOf(value);
	}

	static void init() {
		boolean[] vis = new boolean[100007];
		pri = new int[t];
		for (int i = 0; i < vis.length; ++i)
			vis[i] = false;
		for (int x = 2, tot = 0; tot < pri.length; ++x)
			if (!vis[x]) {
				pri[tot++] = x;
				for (int y = x * 2; y < vis.length; y += x)
					vis[y] = true;
			}
	}

	static int gauss(int n, int m) {
		int i = 0, c = 0;
		for (; i < n && c < m; ++i, ++c) {
			int r = i;
			while (r < n && a[r][c] == 0)
				++r;
			if (r >= n) {
				--i;
				continue;
			}
			if (r != i)
				for (int j = 0; j < m; ++j) {
					int tmp = a[r][j];
					a[r][j] = a[i][j];
					a[i][j] = tmp;
				}
			for (int j = 0; j < n; ++j)
				if (i != j && a[j][c] > 0)
					for (int k = m - 1; k >= c; --k)
						a[j][k] ^= a[i][k];
		}
		return n - i;
	}

	static BigInteger kpow(BigInteger a, int b) {
		BigInteger ret = BigInteger.ONE;
		while (b > 0) {
			if ((b & 1) > 0)
				ret = ret.multiply(a);
			b >>= 1;
			a = a.multiply(a);
		}
		return ret;
	}

	public static void main(String[] argv) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine());
		t = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		a = new int[m][t];
		init();
		st = new StringTokenizer(in.readLine());
		for (int i = 0; i < m; ++i) {
			int x = Integer.parseInt(st.nextToken());
			for (int j = 0; j < t; ++j) {
				int v = 0;
				while (x % pri[j] == 0) {
					v ^= 1;
					x /= pri[j];
				}
				a[i][j] = v;
			}
		}
		int ret = gauss(m, t);
		BigInteger ans = kpow(val(2), ret);
		ans = ans.subtract(val(1));
		System.out.println(ans);
	}
}