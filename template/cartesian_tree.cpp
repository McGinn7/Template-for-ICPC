// time complexity O(N), main property:
// 1.in-order traversal of the tree results in the original sequence.
//   that is, id in left subtree less than the id of root.
// 2.heap property, the parent of node has a smaller value than the 
//   node itself.
int top, sta[N];
void solve() {
	top = 0;
	rep(i, 1, n + 1) {
		int k = top;
		while (k > 0 && a[sta[k]].v > a[i].v) --k;
		if (k > 0) {
			fa[a[i].id] = a[sta[k]].id;
			rs[a[sta[k]].id] = a[i].id;
		}
		if (k < top) {
			fa[a[sta[k + 1]].id] = a[i].id;
			ls[a[i].id] = a[sta[k + 1]].id;
		}
		sta[top = ++k] = i;
	}
}
