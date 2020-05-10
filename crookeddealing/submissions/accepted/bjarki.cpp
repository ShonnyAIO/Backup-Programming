#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

int main() {
    int n, k;
    cin >> n >> k;
    map<int,int> cnt;
    rep(i,0,n) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    priority_queue<ii> pq;
    iter(it,cnt) {
        pq.push(ii(it->second, it->first));
    }

    while (pq.size() >= k) {
        vii take;
        rep(i,0,k) {
            take.push_back(pq.top());
            pq.pop();
        }
        iter(it,take) {
            if (it->first > 1) {
                pq.push(ii(it->first - 1, it->second));
            }
            cout << it->second << " ";
        }
        cout << endl;
    }

    return 0;
}

