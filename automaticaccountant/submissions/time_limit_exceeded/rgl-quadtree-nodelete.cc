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

class QuadTree{
  private:
    pair<int,int> const c1,c2;

    QuadTree *child[2][2]={};
    int size=0;

  public:
    QuadTree(pair<int,int> c1, pair<int,int> c2)
        : c1(c1),
          c2(c2) {}

    virtual ~QuadTree(){
      for (int i=2; i--;) for (int j=2; j--;) delete child[i][j];
    }

    void insert(pair<int,int> const &p){
      ++size;
      if (c1.first+1==c2.first and c1.second+1==c2.second) return;

      pair<int,int> centre={(c1.first+c2.first)/2,(c1.second+c2.second)/2};
      bool const a=(p.first>=centre.first);
      bool const b=(p.second>=centre.second);
      if (not child[a][b]){
        child[a][b]=new QuadTree(
            {a==0? c1.first:  (c1.first+c2.first)/2,
             b==0? c1.second: (c1.second+c2.second)/2},
            {a==0? (c1.first+c2.first)/2: c2.first,
             b==0? (c1.second+c2.second)/2: c2.second});
      }
      child[a][b]->insert(p);
    }

    int find_and_remove(int le_x,int ge_y){
      if (le_x  < c1.first or ge_y >= c2.second) return 0;
      int res=0;

      if (c1.first+1==c2.first and c1.second+1==c2.second){
        res=size;
        size=0;
      }
      else{
        for (int i=2; i--;)
          for (int j=2; j--;)
            if (child[i][j]){
              size-=child[i][j]->size;
              res+=child[i][j]->find_and_remove(le_x,ge_y);
              size+=child[i][j]->size;
            }
      }
      return res;
    }
} tree({0,0}, {1<<20,1<<20});

int main(){
  vector<pair<int,int>> slots; cin>>slots;
  vector<pair<int,int>> coins; cin>>coins;

  for (auto const &i: coins) tree.insert(i);

  unsigned long long res=0;
  for (unsigned long long i=0; i<slots.size(); i++){
    int got=tree.find_and_remove(slots[i].first,slots[i].second);
    res+=(i+1)*got;
  }

  cout<<res<<endl;
}
