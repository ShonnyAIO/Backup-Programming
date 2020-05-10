#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

long long dp[16][1<<16];

constexpr long long infinity=(1ll<<60ll);
constexpr long long s(long long const v){
  return v*v;
}

int main(){
  int rounds; cin>>rounds;
  int n=(1<<rounds);
  vector<int> strength(n); for (auto &i: strength) cin>>i;

  for (int i=0; i<n; i++) dp[rounds][i]=0;
  for (int i=rounds,half=1; i--; half<<=1){
    for (int j=0; j<n; j++){
      dp[i][j]=infinity;
    }
    for (int j=0; j<n; j+=half*2){
      int const l=j,m=j+half,r=m+half;

      for (int a=l; a<m; a++){
        for (int b=m; b<r; b++){
          int const u=(strength[a]>strength[b]? a:b), v=a+b-u;
          dp[i][u]=min(dp[i][u],dp[i+1][u]+dp[i+1][v]);
          dp[i][v]=min(dp[i][v],dp[i+1][u]+dp[i+1][v]+s(strength[a]-strength[b]));
        }
      }
    }
  }
  cout<<dp[0][0]<<endl;
}
