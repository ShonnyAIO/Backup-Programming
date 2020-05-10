#include <bits/stdc++.h>
using namespace std;

int main(){
  int x; cin>>x;
  double l = log10(x);
  int r = (int)l;
  long int p = pow(10,r);
//cout<<x<<endl<<l<<endl<<r<<endl<<p<<endl;
 double d = (double)x / p;
  long int result = round(d) * p;
  cout<<result<<endl;
}
