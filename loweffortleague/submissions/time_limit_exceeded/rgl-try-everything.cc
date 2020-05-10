#include <bits/stdc++.h>
using namespace std;

constexpr int infinity=(1<<29);
constexpr int s(int const v){
  return v*v;
}

int main(){
  int rounds; cin>>rounds;
  int n=(1<<rounds);
  vector<int> strength(n); for (auto &i: strength) cin>>i;
  vector<int> who(n*2);
  for (int i=0; i<n; i++) who[n+i]=i;

  int res=infinity;

  for (vector<bool> will(n); not will[0];){
    // Try this bribery strategy out.
    int cost=0;
    for (int j=n; j-->1;){
      who[j]=who[j*2+(will[j] ^ (strength[who[j*2+1]]>strength[who[j*2]]))];
      if (will[j]) cost+=s(strength[who[j*2]]-strength[who[j*2+1]]);
    }
    if (who[1]==0){
      res=min(res,cost);
      if (cost==2){
        for (auto i: will) cerr<<i; cerr<<endl;
        for (auto i: who) cerr<<i<<" "; cerr<<endl;
      }
    }

    // Increment the "number".
    for (int i=n; i--;) if (not will[i]){
      will[i]=true; while (n>++i) will[i]=false; break;
    }
  }
  cout<<res<<endl;
}
