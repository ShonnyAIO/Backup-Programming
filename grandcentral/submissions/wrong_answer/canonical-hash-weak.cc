#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long Label;

unsigned int constexpr lots=(unsigned int)(1e9L)+7;

bool is_verbose=false;
#define VERBOSE(x) {if(is_verbose){x;}}

struct Hasher{
  unordered_map<int,int> codes;
  unordered_set<int> used;

  int get_hashcode(int x){
    auto const i=codes.find(x);
    if (i==codes.end()){
      int z; do z=rand()%lots; while (used.count(z));
      used.insert(z);
      return codes[x]=z;
    }
    return i->second;
  }
};

struct HashCollection{
  uint32_t cur_hash=0;
  void increase(uint32_t x,Hasher &hasher) {cur_hash=(cur_hash+hasher.get_hashcode(x))%lots;}
  void decrease(uint32_t x,Hasher &hasher) {cur_hash=(cur_hash-hasher.get_hashcode(x)+lots)%lots;}
};

template <int N> struct SeveralHashCollections{
  static Hasher k[N];
  HashCollection h[N]={};

  void increase(uint32_t x) {for (int i=N; i--;) h[i].increase(x,k[i]);}
  void decrease(uint32_t x) {for (int i=N; i--;) h[i].decrease(x,k[i]);}

  Label get(){
    static unordered_map<Label,int> values;
    Label v=0;
    for (int i=N; i--;) v=v*lots+h[i].cur_hash;
    return v;

    if (values.count(v)) return values[v]; else{
      auto const vs=values.size();
      return values[v]=vs;
    }
  }
};
template<int N> Hasher SeveralHashCollections<N>::k[N];

vector<vector<int>> vertex_edge;
vector<unordered_map<int,Label>> vertex_label;
vector<SeveralHashCollections<1>> vertex_collection;

Label calc_label(int x,int p=-1){
  if (vertex_label[x].count(p)){
    return vertex_label[x][p];
  }

  for (int i=vertex_edge[x].size(); i--;){
    if (vertex_edge[x][i]==p){
      if (i==0) break; else swap(vertex_edge[x][i],vertex_edge[x][0]);
    }
    vertex_collection[x].increase(calc_label(vertex_edge[x][i],x));
    vertex_edge[x].pop_back();
  }

  bool rm_parent=(p!=-1 and (vertex_edge[x].size()!=1 or vertex_edge[x][0]!=p));
  if (rm_parent) vertex_collection[x].decrease(calc_label(p,x));
  vertex_label[x][p]=vertex_collection[x].get();
  if (rm_parent) vertex_collection[x].increase(calc_label(p,x));

  // cerr<<"  calc_label "<<x+1<<" "<<p+(p>0)<<" = "<<vertex_label[x][p]<<endl;
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
  vertex_collection.resize(n);

  for (int i=1; i<n; i++){
    int a,b; cin>>a>>b; --a,--b;
    vertex_edge[a].push_back(b);
    vertex_edge[b].push_back(a);
  }

  vector<pair<Label,int>> labels;
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
