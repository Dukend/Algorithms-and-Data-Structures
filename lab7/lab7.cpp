#include <bits/stdc++.h>

using namespace std;
#define fastIO                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
#define fori(k, n) for (int i(k); i < (n); ++i)
#define forj(h, m) for (int j(h); j < (m); ++j)
#define foru(l, p) for (int u(l); u < (p); ++u)
typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;

typedef vector<long long> vll;
typedef vector<int> vi;
typedef pair<ll, ll> pl;

#define MAX_N 100
//ull MOD = 1000000007LL;
//vector<int> G[MAX_N];
//map<ull, ull> m;

void solve() {
    int n, m, ans(0);
    cin >> n >> m;

    // vector<long long>
    vi w(n);
    vi c(n);

    for (int i = 0; i < n; ++i) cin >> w[i] >> c[i];

    bitset<MAX_N> res;
    vector<vi> DPl(n + 1, vi(m + 1));
    vector<vi> DPc(n + 1, vi(m + 1));
    vector<vector<bitset<MAX_N>>> prev(n + 1, vector<bitset<MAX_N>>(m + 1));
    vector<vector<bitset<MAX_N>>> cur(n + 1, vector<bitset<MAX_N>>(m + 1));


    fori(1, n + 1) {
        forj(1, m + 1) {
            DPl[i][j] = DPl[i - 1][j];
            prev[i][j] = prev[i - 1][j];

            if(c[i - 1] > DPl[i][j] and j - w[i - 1] == 0) {
                DPl[i][j] = c[i - 1];
                prev[i][j] = 0;
                prev[i][j][i - 1] = true;
            }
            if(DPl[i][j] > ans) {
                ans = DPl[i][j];
                res = prev[i][j];
            }
        }
    }
    fori(2, n + 1) {
        forj(1, n + 1) {
            foru(1, m + 1) {
                DPc[j][u] = DPc[j - 1][u];
                cur[j][u] = cur[j - 1][u];
                if(u - w[j - 1] > 0 and DPl[j - 1][u - w[j - 1]] > 0) {
                    if((c[j - 1] + DPl[j - 1][u - w[j - 1]] / (i - 1)) * i > DPc[j][u]) {
                        DPc[j][u] = (c[j - 1] + DPl[j - 1][u - w[j - 1]] / (i - 1)) * i;
                        cur[j][u] = prev[j - 1][u - w[j - 1]];
                        cur[j][u][j - 1] = true;
                    }
                }
                if(DPc[j][u] > ans) {
                    ans = DPc[j][u];
                    res = cur[j][u];
                }
            }
        }
        swap(cur, prev);
        swap(DPc, DPl);
    }
    cout << ans << '\n';
    fori(0, n)
        if(res[i])
            cout << i + 1 << ' ';
}

signed main() {
#ifdef _ONPC_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#define TIMEIT
    timeit
#endif // _ONPC_

    fastIO;
    int t(1);
    //cin >> t; // UNCOMMENT IF WITH TESTS //
    fori(0, t) solve();
    cout << '\n';
#ifdef TIMEIT
    endtimeit
#endif // TIMEIT
    return 0;
}