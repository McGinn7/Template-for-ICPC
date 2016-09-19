#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1000005;

int T, n, m;
struct Edge {
    int u, v, w;

    void read() {
        scanf("%d%d%d", &u, &v, &w);
    }

    bool operator < (const Edge& c) const {
        return w < c.w;
    }
} e[N];

int parent[N];
vector<pair<int, int> > g[N];

int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

long long dp[N];
int sz[N];

void dfs(int u, int p) {
    sz[u] = 1;
    dp[u] = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        int w = g[u][i].second;
        if (v == p) continue;
        dfs(v, u);
        dp[u] += dp[v] + 1LL * w * sz[v];
        sz[u] += sz[v];
    }
}

long long tot = 0;
void dfs2(int u, int p, long long sum) {
    tot += sum + dp[u];
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        int w = g[u][i].second;
        if (v == p) continue;
        dfs2(v, u, sum + dp[u] - (dp[v] + 1LL * w * sz[v]) + 1LL * (n - sz[v]) * w);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            parent[i] = i;
        }
        for (int i = 0; i < m; i++) {
            e[i].read();
        }
        sort(e, e + m);
        long long sum = 0;
        for (int i = 0; i < m; i++) {
            int pu = find(e[i].u);
            int pv = find(e[i].v);
            if (pu != pv) {
                sum += e[i].w;
                parent[pv] = pu;
                g[e[i].u].push_back(make_pair(e[i].v, e[i].w));
                g[e[i].v].push_back(make_pair(e[i].u, e[i].w));
            }
        }
        tot = 0;
        dfs(1, 1);
        dfs2(1, 1, 0);
        long long sb = 1LL * n * (n - 1);
        if (n == 1) printf("%I64d %.2f\n", sum, 0);
        else printf("%I64d %.2f\n", sum, tot * 1.0 / sb);
    }
    return 0;
}
