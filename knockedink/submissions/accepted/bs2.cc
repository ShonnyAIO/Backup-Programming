#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

/**
 * Approximation algorithm using Simpson's method.
 * Implementation from: https://www.cnblogs.com/oyking/p/3424999.html
 */

const int maxn=1005;
ld x[maxn],y[maxn],r[maxn];
ld nx[maxn],ny[maxn],nr[maxn];
ld xl[maxn],xr[maxn];

int s[maxn];
inline bool cmp(int a,int b) {
  if(x[a]-r [a] == x[b]-r [b]) return x[a]+r[a]<x[b]+r [b];
  return x[a]-r[a]<x[b]-r [b];
}
inline bool cmp0(int a,int b){return r[a] > r [b];}
int n;
int L,R;
pair<ld,ld> se[maxn];
inline ld f(ld v){
   int sz=0,i,j ;
   ld ret=0.0;
   for(i=L; i<R; ++i){
    if(v <= xl[i] || v >= xr[i]) continue;
    j=s[i];
    ld d=sqrt(r[j]- (v-x [j]) * (v-x[j]));
    se[sz].first=y[j]-d;
    se[sz].second=y[j]+ d;
    ++sz;
   }
   sort(se,se+sz);
   for(i=0; i<sz; ++i){
     ld nowl,nowr;
     nowl=se[i].first;
     nowr=se[i].second;
     for(j=i+1; j<sz; ++j) if(se[j].first > nowr) break;
     else nowr=max(nowr,se[j].second);
     ret += nowr-nowl;
     i=j-1;
   }
   return ret;
}
inline ld rsimp(ld l,ld m,ld r,ld sl,ld sm,ld sr,ld tot){
  ld m1=(l+m) * 0.5,m2=(m+r) * 0.5;
  ld s0=f(m1),s2=f(m2);
  ld gl=(sl+sm+s0+s0+s0+s0)*(m-l),gr=(sm+sr+s2+s2+s2+s2)*(r-m);
  if (abs(gl+gr-tot)<=1e-6L) return gl+gr;
  return rsimp(l,m1,m,sl,s0,sm,gl)+rsimp(m,m2,r,sm,s2,sr,gr);
}

ld area_of_circles(){
  sort(s,s+n,cmp) ;
  ld lo,hi,ans=0.0;
  int i,j;
  for(i=0; i<n; ++i) xl[i]=x[s[i]]-r[s[i]],xr[i]=x[s[i]]+r[s[i]],r[s[i]] *= r[s[i]];
  for(i=0; i<n; ++i){
    ld ilo,ihi;
    ilo=xl[i];
    ihi=xr[i];
    for(j=i+1; j<n; ++j) {
      if (xl[j]>ihi) break;
      ihi=max(ihi,xr[j]);
    }
    ld lo=ilo;
    ld hi=ihi;
    L=i;
    R=j;
    ld mid=(lo+hi) * 0.5;
    ld sl=f(lo),sm=f(mid),sr=f(hi);
    ld tot=sl+sr+sm+sm+sm+sm;
    ans += rsimp(lo,mid,hi,sl,sm,sr,tot);
    i=j-1;
  }
  return ans/6.L;
}

ld total_area(vector<ld> cx,vector<ld> cy,vector<ld> cr){
  n=0;
  for (int i=0; i<cx.size(); i++)
    if (cr[i]>1e-9L)
      x[n]=cx[i],y[n]=cy[i],r[n]=cr[i],s[n]=n,n++;
  sort(s,s+n,cmp0);
  int j=0,k=0;
  for (int i=0; i<n; i++){
    bool ok=true;
    for (k=0; k<j; k++) ok&=(nr[j]<hypotl(nx[i]-nx[k],ny[i]-ny[k])+nr[i]+1e-10L);
    if (ok){
      nx[j]=x[s[i]];
      ny[j]=y[s[i]];
      nr[j]=r[s[i]];
      s[j]=j;
      j++;
    }
  }
  n=j;

  return area_of_circles();
}

int main(){
  ld angle=1.45692586256L;

  int n; ld area; cin>>n>>area;
  vector<ld> cx(n),cy(n),cr(n);
  for (int i=n; i--;){
    ld x,y,r; cin>>x>>y>>r;
    cx[i]=cosl(angle)*x+sinl(angle)*y;
    cy[i]=cosl(angle)*y-sinl(angle)*x;
    cr[i]=r;
  }

  ld min_rad=cr[0];
  for (auto const &i: cr) min_rad=min(min_rad,i);

  ld lef=min_rad;
  ld rgt=min_rad+sqrtl(area/M_PI);
  for (int iter=200; iter--;){
    ld const mid=(lef+rgt)/2.L;

    vector<ld> tcr=cr;
    for (int i=0; i<n; i++) tcr[i]=max(mid-cr[i],0.L);
    ld const total=total_area(cx,cy,tcr);
    if (total<area){
      lef=mid;
    }else{
      rgt=mid;
    }
  }

  cout.precision(12);
  cout<<fixed<<lef<<endl;
}

