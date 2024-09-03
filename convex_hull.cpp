struct Node {
  int x, y;
  Node() {}
  Node(int _x, int _y) { x = _x, y = _y; }
  bool operator<(const Node &p) const { return x != p.x ? x < p.x : y < p.y; }
  Node operator-(const Node &p) const { return Node(x - p.x, y - p.y); }
  ll operator/(const Node &p) const { return 1ll * x * p.y - 1ll * y * p.x; }
};

struct SemiConvexHull {
  ll area;
  set<Node> v;

  bool positive(const Node &p) {
    auto nxt = v.lower_bound(Node(p.x, INT_MIN));
    if (v.end() == nxt) return false;
    if (nxt->x == p.x) return nxt->y <= p.y;
    if (v.begin() == nxt) return false;
    auto pre = prev(nxt);
    return (*nxt - *pre) / (p - *pre) >= 0;
  }

  void add(const Node &p) {
    if (positive(p)) return;
    auto iter = v.insert(p).first;
    if (v.size() > 1) {
      const Node &pre = v.begin() == iter ? Node(0, 0) : *prev(iter);
      const Node &nxt = v.end() == next(iter) ? Node(0, 0) : *next(iter);
      area += pre / p + p / nxt - pre / nxt;
    }
    auto a = iter, b = iter, c = iter;
    auto process = [&]() {
      if ((*b - *a) / (*c - *a) >= 0) return false;
      area += *a / *c - *a / *b - *b / *c;
      v.erase(b);
      return true;
    };
    if (v.begin() != iter) {
      for (b = prev(iter), c = iter; v.begin() != b; b = a) {
        a = prev(b);
        if (!process()) break;
      }
    }
    if (v.end() != next(iter) && v.end() != next(iter, 2)) {
      for (a = iter, b = next(iter); v.end() != next(b); b = c) {
        c = next(b);
        if (!process()) break;
      }
    }
  }
};

struct ConvexHull {
  SemiConvexHull up, dw;

  ll area() {
    if (dw.v.size() < 2) return 0;
    ll ret = up.area + dw.area;
    ret += (*dw.v.rbegin()) / Node(up.v.rbegin()->x, -up.v.rbegin()->y);
    ret += Node(up.v.begin()->x, -up.v.begin()->y) / (*dw.v.begin());
    return abs(ret);
  }

  bool contain(int x, int y) {
    return up.positive(Node(x, -y)) && dw.positive(Node(x, y));
  }

  void add(int x, int y) {
    up.add(Node(x, -y));
    dw.add(Node(x, y));
  }
} ch;
