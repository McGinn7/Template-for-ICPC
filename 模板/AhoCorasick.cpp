template<int V>
struct AhoCorasick {
	bool end[V];
	int size, link[V], queue[V], trie[V][10];
	AhoCorasick() {
		init();
	}
	int addNode() {
		memset(trie[size], 0, 10 * sizeof(int));
		link[size] = 0;
		end[size] = false;
		return size++;
	}
	void init() {
		size = 0;
		addNode();
	}
	void addString(const char *str, int len) {
		int state = 0;
		for (int i = 0; i < len; ++i) {
			int c = str[i];
			if (!trie[state][c])
				trie[state][c] = addNode();
			state = trie[state][c];
		}
		end[state] = true;
	}
	void build() {
		queue[0] = 0;
		for (int head = 0, tail = 1; head < tail; ++head) {
			int v = queue[head];
			for (int c = 0; c < 10; ++c)
				if (trie[v][c]) {
					int u = link[v];
					while (u && !trie[u][c])
						u = link[u];
					link[trie[v][c]] = (!v ? 0 : trie[u][c]);
					queue[tail++] = trie[v][c];
				} else {
					trie[v][c] = trie[link[v]][c];
				}
		}

	}
};
AhoCorasick<(N * M) / 2> ac;
