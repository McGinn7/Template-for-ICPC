// Main properties:
// 1.In-order traversal of the tree results in the original sequence.
// 2.Heap property, the parent of node has a smaller value than the 
//   node itself.

struct Node {
	int parent, left, right;
} node[MAXN];
 
struct Info {
	int idx, key, val;
	bool operator<(const Info &i) const {
		return key < i.key;
	}
} info[MAXN];

namespace CartesianTree {
	int *top, stc[MAXN];
 
	void addLeft(int x, int y) {
		node[x].left = y, node[y].parent = x;
	}
 
	void addRight(int x, int y) {
		node[x].right = y, node[y].parent = x;
	}
 
	void build(int N, Info *info) {
		sort(info, info + N);
		rep(i, 0, N) node[i] = (Node){-1, -1, -1};
 
		top = stc;
		rep(i, 0, N) {
			int *tmp = top;
			int idx = info[i].idx;
			int val = info[i].val;
			while (tmp > stc && info[*tmp].val > val) --tmp;
			if (tmp > stc) addRight(info[*tmp].idx, idx);
			if (tmp < top) addLeft(idx, info[*(tmp + 1)].idx);
			*(top = ++tmp) = i;	
		}
	}
};