#include <bits/stdc++.h>
using namespace std;

template <int64_t mod,int64_t factor>
struct Hash{
  int64_t value=0;
  void add(int64_t x){
    value=(int64_t)((value*(__int128)factor+x)%(__int128)mod);
  }
  Hash operator+(Hash const &other)const{
    return {(value+other.value)%mod};
  }
  Hash operator-(Hash const &other)const{
    return {(mod+value-other.value)%mod};
  }
  Hash operator*(int64_t const by)const{
    return {(int64_t)((value*(__int128)by)%(__int128)mod)};
  }
  bool operator==(Hash const &other)const{
    return value==other.value;
  }
  bool operator<(Hash const &other)const{
    return value<other.value;
  }
};

struct Hashes{
  Hash<6660000000001ll,251429ll> a;
  Hash<2345678911111111ll,11111117ll> b;
  Hash<9999999900000001ll,16431563ll> c;
  void add(int64_t const x){
    a.add(x);
    b.add(x);
    c.add(x);
  }
  bool operator==(Hashes const &other)const{
    return a==other.a and b==other.b and c==other.c;
  }
  Hashes operator+(Hashes const &other)const{
    return {a+other.a,b+other.b,c+other.c};
  }
  Hashes operator-(Hashes const &other)const{
    return {a-other.a,b-other.b,c-other.c};
  }
  bool operator<(Hashes const &other)const{
    return a==other.a? b==other.b? c<other.c: b<other.b: a<other.a;
  }
  Hashes operator*(int const by)const{
    return {a*by,b*by,c*by};
  }
};

namespace std{
  template<>
  struct hash<Hashes>{
    size_t operator()(Hashes const &k)const{
      return k.a.value^k.b.value^k.c.value;
    }
  };
}

vector<pair<Hashes,int>> go(Hashes *const s,Hashes *const t){
  vector<pair<Hashes,int>> h(1);
  h.reserve(1<<(t-s));
  for (auto i=s; i!=t; i++)
    for (size_t j=0; j*2<h.size(); j++)
      h.emplace_back(*i+h[j].first,h[j].second+1);
  sort(h.begin(),h.end());
  return h;
}

int main(){
  ios::sync_with_stdio(false);
  int n,m,c; cin>>n>>m>>c;

  static Hashes hashes[40];
  {
    for (int i=0; i<n; i++){
      vector<int> freq(c);
      for (int j=0; j<m; j++){
        int x; cin>>x; assert(1<=x and x<=c); ++freq[x-1];
      }
      for (int j=0; j<c; j++){
        hashes[i].add(freq[j]);
      }
      /*
      cerr<<     hashes[i].a.value
          <<" "<<hashes[i].b.value
          <<" "<<hashes[i].c.value<<endl;
      */
    }
  }

  vector<Hashes> good={Hashes{}};
  Hashes basic;
  for (int i=0; i<c; i++){
    basic.add(1);
  }
  for (int i=1; i<=n; i++){
    if ((i*m)%c==0){
      good.push_back(basic*(i*m/c));
      /*
      cerr<<"  value="<<i*m/c<<endl;
      cerr<<"    "<<good.back().a.value
          <<"    "<<good.back().b.value
          <<"    "<<good.back().c.value<<endl;
      */
    }
  }

  auto const left=go(hashes,hashes+n/2);
  auto const right=go(hashes+n/2,hashes+n);
  int res=0;

  for (auto const &total: good){
    for (pair<Hashes,int> const &l: left){
      auto const want=total-l.first;
      auto it=lower_bound(right.begin(),right.end(),make_pair(want,0));
      if (it!=right.end() and it->first==want){
        res=max(res,l.second+it->second);
      }
    }
  }
  cout<<res<<endl;
}
