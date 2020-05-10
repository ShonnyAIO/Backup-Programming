#include <bits/stdc++.h>
using namespace std;

bool is_verbose=false;
#define VERBOSE(x) {if(is_verbose){x;}}

vector<set<int>> vertex_edge;
vector<map<int,int>> vertex_label;

int make_label(vector<int> const &s){
  static map<vector<int>,int> labels;
  static int next_id=0;
  return labels.count(s)? labels[s]: (labels[s]=next_id++);
}

int calc_label(int x,int p=-1){
  if (vertex_label[x].count(p)){
    return vertex_label[x][p];
  }

  set<int> children=vertex_edge[x];
  children.erase(p);

  vector<int> items;
  for (auto y: children) items.push_back(calc_label(y,x));
  sort(items.begin(),items.end());
  vertex_label[x][p]=make_label(items);

  return vertex_label[x][p];
}

int main(int argc,char **argv){
  while (argc-->1){
    if (string("-v")==argv[argc]){
      is_verbose=true;
    }
  }

  int n; cin>>n;
  vertex_edge.resize(n);
  vertex_label.resize(n);

  for (int i=1; i<n; i++){
    int a,b; cin>>a>>b; --a,--b;
    vertex_edge[a].insert(b);
    vertex_edge[b].insert(a);
  }

  vector<pair<int,int>> labels;
  for (int i=n; i--;){
    VERBOSE(cerr<<"label "<<i+1<<" = "<<calc_label(i)<<endl);
    labels.emplace_back(calc_label(i),i);
  }
  sort(labels.begin(),labels.end());
  int res=1;
  for (int i=n; i-->1;){
    res+=(labels[i].first!=labels[i-1].first);
  }
  cout<<res<<endl;
}
