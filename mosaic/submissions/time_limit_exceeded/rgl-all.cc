#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,m,c; cin>>n>>m>>c;

  vector<vector<int>> freq(n,vector<int>(c));
  for (int i=0; i<n; i++){
    for (int j=0; j<m; j++){
      int x; cin>>x; ++freq[i][x-1];
    }
  }

  int res=0;
  for (int64_t mask=0; mask!=(1ll<<(int64_t)n); mask++){
    int q=__builtin_popcountl(mask); if (q<=res) continue;
    if ((q*m)%c) continue;
    int need=q*m/c;

    for (int j=0; j<c; j++){
      int sum=0;
      for (int64_t i=0; i<n; i++)
        if (mask&(1ll<<i))
           sum+=freq[i][j];
      if (sum!=need) goto bad;
    }

    res=q;
    bad: continue;
  }
  cout<<res<<endl;
}
