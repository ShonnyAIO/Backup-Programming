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

unordered_map<Hashes,int> go(Hashes *const s,Hashes *const t){
  vector<Hashes> h(1);
  for (auto i=s; i!=t; i++)
    for (size_t j=0; j*2<h.size(); j++)
      h.push_back(*i+h[j]);
  unordered_map<Hashes,int> res;
  for (auto j=h.size(); j--;)
    res[h[j]]=__builtin_popcount(j);
  return res;
}

int main(){
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

  unordered_map<Hashes,int> const left=go(hashes,hashes+n/2),
                                  right=go(hashes+n/2,hashes+n);
  int res=0;
  for (auto const &total: good){
    for (pair<Hashes,int> const &l: left){
      auto const want=total-l.first;
      if (right.count(want)){
        res=max(res,l.second+right.at(want));
      }
    }
  }
  cout<<res<<endl;
}
