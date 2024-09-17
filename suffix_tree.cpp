const int N = 1e6 + 7;
const int N2 = N * 2;
const int E = 27;

struct SuffixTree {
	short s[N];
	int n, m, act, rem, pos[N2], len[N2], link[N2], ch[N2][E];

	SuffixTree() {
		n = rem = 0, act = 1, m = 2, len[0] = INT_MAX;
	}

	int new_node(int p, int l) {
		pos[m] = p, len[m] = l;
		return m++;
	}

	void append(const short x, const int root = 1) {
		s[++n] = x, ++rem;
		for (int last = root; rem > 0; ) {
			while (rem > len[ch[act][s[n - rem + 1]]]) {
				act = ch[act][s[n - rem + 1]];
				rem -= len[act];
			}
			int &v = ch[act][s[n - rem + 1]];
			auto c = s[pos[v] + rem - 1];
			if (!v) {
				last = link[last] = act;
				v = new_node(n, INT_MAX);
			} else if (x == c) {
				last = link[last] = act;
				break;
			} else {	
				int u = new_node(pos[v], rem - 1);
				ch[u][c] = v;
				ch[u][x] = new_node(n, INT_MAX);
				pos[v] += rem - 1;
				len[v] -= rem - 1;
				last = link[last] = v = u;
			}
			root == act ? --rem : act = link[act];
		}
	}
} st;
