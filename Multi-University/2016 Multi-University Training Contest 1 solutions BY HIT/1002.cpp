#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = (1<<20);

int T, n, sg[N];
int vis[N];

int dfs(int s) {
    if (sg[s] != -1) return sg[s];
    int pre = 0, sgg = 0;
    for (int i = 0; i < 20; i++) {
        if (s&(1<<i)) continue;
        for (int j = i - 1; j >= 0; j--) {
            if ((s&(1<<j)) == 0) break;
            sgg |= (1<<dfs(s^(1<<i)^(1<<j)));
        }
    }
    for (int i = 0; i < 20; i++) if ((sgg&(1<<i)) == 0) {
        sg[s] = i;
        break;
    }
    return sg[s];
}

int main() {
    memset(sg, -1, sizeof(sg));
    for (int i = 0; i < (1<<20); i++) {
        if (sg[i] != -1) continue;
        sg[i] = dfs(i);
    }
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int k;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &k);
            int x, ss = 0;
            while (k--) {
                scanf("%d", &x);
                x--;
                ss ^= (1<<x);
            }
            ans ^= sg[ss];
        }
        printf("%s\n", ans ? "YES" : "NO");
    }
    return 0;
}