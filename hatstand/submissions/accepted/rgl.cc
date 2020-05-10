#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,m; cin>>n>>m;
  vector<int> p(m);
  for (int &i: p) cin>>i;

  vector<int> place(n+1);
  vector<pair<int,int>> slots(n);
  for (int i=0; i<n; i++) slots[i]={0,i+1}, place[i+1]=i;

  for (int i=1; i<m; i++){
    slots[place[p[i]]].first++;
    swap(place[p[i]],place[p[i-1]]);
  }

  slots.erase(slots.begin()+p[0]-1);
  sort(slots.begin(),slots.end());
  int64_t cost=0;
  for (int i=0; i<slots.size(); i++){
    cost+=(slots.size()-i)*(int64_t)slots[i].first;
  }
  cout<<cost<<endl;
  for (int i=slots.size(); i--;){
    cout<<slots[i].second<<(i==0?'\n':' ');
  }
}
