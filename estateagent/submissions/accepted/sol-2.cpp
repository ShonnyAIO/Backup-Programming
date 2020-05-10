#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const ll INF = 1000000000000000000LL;

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<ll> > a(n+1, vector<ll>(n+1, INF));

    rep(i,1,n+1) {
        a[i][i] = 0;
    }

    rep(i,0,k) {
        int f,g;
        ll c;
        cin >> f >> g >> c;
        a[f][g] = min(-c, a[f][g]);
    }

    int m = n;

    vector<ll> u (n+1), v (m+1), p (m+1), way (m+1);
    for (ll i=1; i<=n; ++i) {
        p[0] = i;
        ll j0 = 0;
        vector<ll> minv (m+1, INF);
        vector<char> used (m+1, false);
        do {
            used[j0] = true;
            ll i0 = p[j0],  delta = INF,  j1;
            for (ll j=1; j<=m; ++j)
                if (!used[j]) {
                    ll cur = a[i0][j]-u[i0]-v[j];
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            for (ll j=0; j<=m; ++j)
                if (used[j])
                    u[p[j]] += delta,  v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            ll j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    ll cost = v[0];
    ll rem = 5 * (cost % 20);
    cout << cost / 20 << "." << rem / 10 << rem % 10 << endl;

    return 0;
}

