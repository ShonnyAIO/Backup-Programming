#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename A, typename B>
istream &operator>>(istream &is, pair<A,B> &p){
  return is>>p.first>>p.second;
}

template <typename C>
istream &operator>>(istream &is, vector<C> &v){
  int n; is>>n;
  v.resize(n);
  for (auto &i: v) is>>i;
  return is;
}

int main(){
  vector<pair<int,int>> slots; cin>>slots;
  vector<pair<int,int>> coins; cin>>coins;

  unsigned long long res=0;
  for (auto const &i: coins){
    for (int j=0; j<slots.size(); j++)
      if (slots[j].first >= i.first and slots[j].second <= i.second){
        res+=j+1;
        break;
      }
  }

  cout<<res<<endl;
}
