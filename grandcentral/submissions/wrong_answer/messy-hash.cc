#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long Label;

Label constexpr lots=100000000000031ll;

vector<vector<int>> vertex_edge;
vector<pair<Label,int>> labels;

Label calc_label(int x){
  Label res=(labels[x].first+123)%lots;

  vector<Label> edges;
  for (int y: vertex_edge[x]) edges.push_back(labels[y].first);
  sort(edges.begin(),edges.end());

  for (Label i: edges){
    res=(res*15013ll+i*13ll)%lots;
  }
  return res;
}

int main(int argc,char **argv){
  int n; cin>>n;
  vertex_edge.resize(n);
  labels.resize(n);

  for (int i=1; i<n; i++){
    int a,b; cin>>a>>b; --a,--b;
    vertex_edge[a].push_back(b);
    vertex_edge[b].push_back(a);
  }

  for (int z=50; z--;){
    vector<pair<Label,int>> new_labels(n);
    for (int i=n; i--;){
      new_labels[i]={calc_label(i),i};
    }
    labels=new_labels;
  }

  sort(labels.begin(),labels.end());
  int res=1;
  for (int i=n; i-->1;){
    res+=(labels[i].first!=labels[i-1].first);
  }
  cout<<res<<endl;
}
