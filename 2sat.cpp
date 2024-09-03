// 可行解套tarjan判环

// 最小解
vi e[N];
bool dfs(int u) {
    if (col[u] == -1)
        return false;
    if (col[u] == 1)
        return true;
    ans[tot++] = u;
    col[u] = 1, col[u ^ 1] = -1;
    rep(i, 0, sz(e[u])) {
        int v = e[u][i];
        if (!dfs(v))
            return false;
    }
    return true;
}
bool solve() {
    rep(i, 0, n) {
        if (col[i] != 0)
            continue;
        tot = 0;
        if (!dfs(i)) {
            rep(j, 0, tot) {
                int u = ans[j];
                col[u] = col[u ^ 1] = 0;
            }
            if (!dfs(i ^ 1))
                return false;
        }
    }
    return true;
}

// 一种可行解
struct TwoSat {
    int n;
    vector<int> g[MAXNODE];
    int pre[MAXNODE], dfn[MAXNODE], dfs_clock, sccn, sccno[MAXNODE];
    stack<int> S;
    int mark[MAXNODE];

    void init(int tot) {
        n = tot * 2;
        for (int i = 0; i < n; i += 2) {
            g[i].clear();
            g[i ^ 1].clear();
        }
    }

    void add_Edge(int u, int uval, int v, int vval) {
        u = u * 2 + uval;
        v = v * 2 + vval;
        g[u ^ 1].push_back(v);
        g[v ^ 1].push_back(u);
    }

    void dfs_scc(int u) {
        pre[u] = dfn[u] = ++dfs_clock;
        S.push(u);
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (!pre[v]) {
                dfs_scc(v);
                dfn[u] = min(dfn[u], dfn[v]);
            } else if (!sccno[v])
                dfn[u] = min(dfn[u], pre[v]);
        }
        if (pre[u] == dfn[u]) {
            sccn++;
            while (1) {
                int x = S.top();
                S.pop();
                sccno[x] = sccn;
                if (x == u)
                    break;
            }
        }
    }
    void find_scc() {
        dfs_clock = sccn = 0;
        memset(sccno, 0, sizeof(sccno));
        memset(pre, 0, sizeof(pre));
        for (int i = 0; i < n; i++)
            if (!pre[i])
                dfs_scc(i);
    }
    bool solve() {
        find_scc();
        for (int i = 0; i < n; i += 2) {
            if (sccno[i] == sccno[i + 1])
                return false;
            mark[i / 2] = (sccno[i] > sccno[i + 1]);
        }
        return true;
    }
} gao;
