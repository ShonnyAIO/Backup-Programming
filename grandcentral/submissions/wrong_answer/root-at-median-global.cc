#include <bits/stdc++.h>
using namespace std;

map<vector<int>,int> label_map;
map<int,vector<int>> label_hits;

set<int> edges[1000001];
int p[1000001];

pair<int,int> farthest(int x,int r){
  p[x]=r;
  pair<int,int> res={0,x};
  for (int y: edges[x])
    if (y!=r){
      auto d=farthest(y,x); ++d.first;
      res=max(res,d);
    }
  return res;
}

int farthest(int x) {
  return farthest(x,-1).second;
}

int establish_labels(int x,int r=-1){
  vector<int> c;
  for (auto y: edges[x])
    if (y!=r)
      c.emplace_back(establish_labels(y,x));
  sort(c.begin(),c.end());

  int l;
  if (not label_map.count(c)){
    l=label_map.size();
    label_map[c]=l;
  }else{
    l=label_map[c];
  }

  label_hits[l].push_back(x);
  return l;
}

int main(int argc,char **argv){
  int n; cin>>n;

  for (int i=1; i<n; i++){
    int a,b; cin>>a>>b; --a,--b;
    edges[a].insert(b); edges[b].insert(a);
  }

  // Find a pair of farthest vertices to get the median from.
  int x=farthest(farthest(farthest(0)));
  vector<int> path={x};
  while (p[path.back()]!=-1) path.push_back(p[path.back()]);

  int median=path[path.size()/2];
  int virtual_nodes=0;

  // Create a virtual median if necessary.
  if (path.size()%2==0){
    int const a=path[(path.size()-1)/2];
    int const b=path[(path.size()+1)/2];
    edges[a].erase(b); edges[b].erase(a);
    edges[a].insert(n); edges[n].insert(a);
    edges[b].insert(n); edges[n].insert(b);
    median=n++;
    ++virtual_nodes;
  }

  establish_labels(median);
  cout<<label_hits.size()-virtual_nodes<<endl;
}
