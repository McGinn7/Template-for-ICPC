struct Node {
	int zone;
	ll x, y;
	Node() {
	}
	Node(ll _x, ll _y) {
		x = _x, y = _y, zone = (x >= 0) ^ (1 << (y < 0));
	}
	ll operator^(const Node &p) const {
		return x * p.y - y * p.x;
	}
};
bool cmp(const Node &p, const Node &q) {
	if (p.zone != q.zone) return p.zone < q.zone; // 象限
	if ((p ^ q) != 0) return (p ^ q) > 0; // 角度
	return sqr(p.x) + sqr(p.y) < sqr(q.x) + sqr(q.y); // 距离
}
