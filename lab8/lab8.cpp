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
static double eps = numeric_limits<double>::epsilon();
#define MAX_N 50
//ull MOD = 1000000007LL;
//vector<int> G[MAX_N];
//map<ull, ull> m;

struct Row: vector<double>{
    ll num;
    ll cost;
};

void solve() {
    ll m, n;
    cin >> m >> n;
    vector<Row> matr(m);

    set<ll> ans;

    fori(0, matr.size()) {
        Row& row = matr[i];
        row.num = i+1;
        row.resize(n);
        for(double &el : row) cin >> el;
        cin >> row.cost;
    }

    // just find similar upper-triangle matrix
    fori(0, n){
        ll min_cost = MAX_N + 1;
        ll min_idx;
        forj(i, m) {
            if(abs(matr[j][i]) > eps && matr[j].cost < min_cost){
                min_idx = j;
                min_cost = matr[j].cost;
            }
        }
        if(min_cost == MAX_N + 1){
            cout << -1 << '\n';
            exit(0);
        }

        ans.insert(matr[min_idx].num);
        swap(matr[i], matr[min_idx]); // where we started and what we found

        forj(i + 1, m) { // change all bottom rows
            double coefficient = matr[j][i] / matr[i][i]; // coefficient for current row
            foru(i, n) { // start from first not calc column
                matr[j][u] -= matr[i][u] * coefficient;
            }
        }
    }
    // print answer
    for (const ll& elem: ans)
        cout << elem << ' ';
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