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

struct Segment{
  int value;
  int l_level;
  int r_level;
};

static vector<Segment> tree[1<<19];

void insert(int x,int y){
  for (int i=(1<<18)+x; i; i>>=1){
    tree[i].push_back({
      (tree[i].empty()? y: min(tree[i].back().value,y)),
      i>=(1<<18)? -1: (int) tree[i*2+0].size()-1,
      i>=(1<<18)? -1: (int) tree[i*2+1].size()-1
    });
  }
}

int get(int a,int b,int level, int i=1,int l=0,int r=(1<<18)){
  if (level<0) return (1<<29);
  if (b<=l || r<=a) return (1<<29);
  if (a<=l && r<=b) return tree[i][level].value;

  int const m=(l+r)/2;
  return min(
    get(a,b,tree[i][level].l_level, i*2+0,l,m),
    get(a,b,tree[i][level].r_level, i*2+1,m,r)
  );
}

int main(){
  int res=0;

  vector<pair<int,int>> slots; cin>>slots;
  for (auto const &i: slots){
    insert(i.first,i.second);
  }
  vector<pair<int,int>> coins; cin>>coins;

  for (auto const &i: coins){
    int l=0;
    for (int rad=(1<<29); rad; rad>>=1){
      int m=(l+rad);
      if (m<=slots.size() and get(i.first,(1<<29),m-1)>i.second){
        l=m;
      }
    }
    // cerr<<l+1<<endl;
    res+=l+1;
  }

  cout<<res<<endl;
}
