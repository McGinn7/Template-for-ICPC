struct KM { // 最大权匹配
    int n, m; // 左边n个点，右边m个点，必须满足n<=m!
    bool vis[M];
    double Lx[N], Ly[M], slack[M], g[N][M];
    int pre[M], left[M]; // left[i]和i匹配
    void init(int _n, int _m) {
        n = _n, m = _m;
        rep(i, 0, n)
            rep(j, 0, m)
                g[i][j] = -LINF;
        memset(Lx, 0, sizeof(Lx[0]) * n);
        memset(Ly, 0, sizeof(Ly[0]) * m);
        memset(left, -1, sizeof(left[0]) * m);
    }
    void addEdge(int u, int v, double val) {
        g[u][v] = val;
    }
    void go(int now) {
        rep(i, 0, m + 1)
            vis[i] = false, slack[i] = LINF;
        left[m] = now;
        int u = m;
        while (~left[u]) {
            vis[u] = true;
            double d = LINF;
            int v;
            rep(i, 0, m)
                if (!vis[i]) {
                    double tmp = Lx[left[u]] + Ly[i] - g[left[u]][i];
                    if (sign(tmp - slack[i]) < 0)
                        slack[i] = tmp, pre[i] = u;
                    if (sign(slack[i] - d) < 0)
                        d = slack[v = i];
                }
            rep(i, 0, m + 1)
                if (vis[i])
                    Lx[left[i]] -= d, Ly[i] += d;
                else
                    slack[i] -= d;
            u = v;
        }
        while (u != m)
            left[u] = left[pre[u]], u = pre[u];
    }
    double run() {
        rep(i, 0, n)
            go(i);
        double ans = 0;
        rep(i, 0, n)
            ans += Lx[i];
        rep(i, 0, m)
            ans += Ly[i];
        return ans;
    }
} km;
