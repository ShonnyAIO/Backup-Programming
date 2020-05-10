#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,x; cin>>n>>x;
  vector<int> v(n); for (int &i: v) cin>>i;
  sort(v.begin(),v.end());
  priority_queue<pair<int,int>> pq;
  for (int i=0,j=0; i<v.size(); pq.emplace(i-j,v[j])) for (j=i; i<v.size() and v[i]==v[j]; i++);

  auto pecrease=[&pq,&n](){auto t=pq.top(); if (--t.first) pq.push(t); pq.pop(); --n; return t.second;};

  for (int m=n/x; m>0; --m){
    while (not pq.empty() and pq.top().first>m) pecrease();
    if (m*x<=n){
      vector<int> res; while (not pq.empty()) res.push_back(pecrease()); sort(res.begin(),res.end());
      for (int i=0; i<m; i++) for (int j=0; j<x; j++) cout<<res[i+j*m]<<(j+1==x?'\n':' ');
      return 0;
    }
  }
  cout<<"impossible"<<endl;
}
