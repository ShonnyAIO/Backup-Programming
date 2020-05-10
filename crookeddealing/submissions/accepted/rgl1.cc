#include <bits/stdc++.h>

std::vector<int> troup(std::vector<int> const &v,int const ms){
  std::vector<int> res;
  for (int i=0; i<v.size();) for (int j=i; i<v.size() and v[i]==v[j]; i++) if (i-j<ms) res.push_back(v[i]);
  return res;
}

int main(){
  int n,x; std::cin>>n>>x;
  std::vector<int> v(n); for (int &i: v) std::cin>>i;
  std::sort(v.begin(),v.end());

  int lef=0,rgt=n+1;
  while (lef+1<rgt) (troup(v,(lef+rgt)/2).size() >= ((lef+rgt)/2)*x? lef: rgt)=(lef+rgt)/2;
  if (lef==0){
    puts("impossible");
  }else{
    auto const res=troup(v,lef);
    for (int i=0; i<lef; i++)
        for (int j=0; j<x; j++)
          std::cout<<res[i+j*lef]<<(j+1==x?'\n':' ');
  }
}
