#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int N = 15;
const int INF = 0x3f3f3f3f;

bool bmask[N];
int nx, ny, dis;
int cx[N], cy[N];
int dx[N], dy[N];
vector<int> g[N];

bool searchpath() {
    queue<int> Q;
    dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for(int i = 0; i < nx; i++) {
        if(cx[i] == -1) {
            Q.push(i);
            dx[i] = 0;
        }
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if(dx[u] > dis) break;
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if(dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if(cy[v] == -1) dis = dy[v];
                else {
                    dx[cy[v]] = dy[v] + 1;
                    Q.push(cy[v]);
                }
            }
        }
    }
    return dis != INF;
}

bool findpath(int u) {
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(!bmask[v] && dy[v] == dx[u] + 1) {
            bmask[v] = 1;
            if(cy[v] != -1 && dy[v] == dis)
                continue;
            if(cy[v] == -1 || findpath(cy[v])) {
                cy[v] = u; cx[u] = v;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch() {
    int res = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    while(searchpath()) {
        memset(bmask, 0, sizeof(bmask));
        for(int i = 0; i < nx; i++) {
            if(cx[i] == -1)
                res += findpath(i);
        }
    }
    return res;
}

int n, m;
int c[N][N];
int id[N], a[N];

int cal() {
    for (int i = 0; i < n; i++) g[i].clear();
    nx = ny = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int jj = j - 1;
            if (jj < 0) jj += n;
            if ((c[i][a[jj]] + c[i][a[j]]) > 0) continue;
            g[i].push_back(j);
        }
    }
    return n - MaxMatch();
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(c, 0, sizeof(c));
        int u, v;
        while (m--) {
            scanf("%d%d", &u, &v);
            u--; v--;
            c[u][v] = 1;
        }
        if (n == 0) {
            printf("0\n");
            continue;
        }
        int ans = n;
        for (int i = 0; i < n - 1; i++) id[i] = i;
        do {
            a[0] = 0;
            for (int i = 0; i < n - 1; i++) a[i + 1] = id[i] + 1;
            ans = min(ans, cal());
        } while(next_permutation(id, id + n - 1));
        printf("%d\n", ans);
    }
    return 0;
}