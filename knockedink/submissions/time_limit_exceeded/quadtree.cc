#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

/**
 * Estimate area of circles using a quad tree.
 */

#define DEBUGV(x)
#define DEBUG(x) x

struct Circle{
  ld x,y,r;
  bool contains(ld a,ld b,ld adjust=0)const{
    return hypotl(a-x,b-y)<=r+adjust;
  }
};

/**
 * Circle-square intersection from https://stackoverflow.com/a/32698993
 */

ld section(ld h,ld r = 1){
  return (h<r)? sqrtl(r*r-h*h) : 0;
}

ld g(ld x,ld h,ld r = 1){
  return (sqrtl(1-x*x/(r*r))*x*r+r*r*asinl(x/r)-2*h*x)/2;
}

ld area(ld x0,ld x1,ld h,ld r){
  if(x0 > x1) swap(x0,x1);
  ld s = section(h,r);
  return g(max(-s,min(s,x1)),h,r) - g(max(-s,min(s,x0)),h,r);
}

ld area(ld x0,ld x1,ld y0,ld y1,ld r){
  if(y0>y1) swap(y0,y1);
  if(y0<0) {
    if(y1<0)
      return area(x0,x1,-y0,-y1,r);
    else
      return area(x0,x1,0,-y0,r) + area(x0,x1,0,y1,r);
  } else {
    assert(y1>=0);
    return area(x0,x1,y0,r) - area(x0,x1,y1,r);
  }
}

ld area(ld x0, ld x1, ld y0, ld y1, ld cx, ld cy, ld r){
  ld const res=area(x0-cx, x1-cx, y0-cy, y1-cy, r);
  return res;
}

ld solve(vector<Circle> const &c,ld minx=-1e7,ld maxx=1e7,ld miny=-1e7,ld maxy=1e7,int depth=0){
  DEBUGV(cerr<<minx<<" "<<maxx<<" | "<<miny<<" "<<maxy<<endl);
  if (c.empty()) return 0;
  assert(minx<=maxx);
  assert(miny<=maxy);

  ld mincx=maxx,maxcx=minx,mincy=maxy,maxcy=miny;
  for (auto const &i: c){
    mincx=min(mincx,i.x-i.r), maxcx=max(maxcx,i.x+i.r);
    mincy=min(mincy,i.y-i.r), maxcy=max(maxcy,i.y+i.r);
  }
  minx=max(minx,mincx); maxx=min(maxx,maxcx);
  miny=max(miny,mincy); maxy=min(maxy,maxcy);

  bool any=false;
  for (auto const &i: c){
    if (i.contains(minx,miny) and i.contains(maxx,miny) and i.contains(minx,maxy) and i.contains(maxx,maxy)){
      DEBUGV(cerr<<"    box "<<minx<<" "<<maxx<<" | "<<miny<<" "<<maxy<<" = "<<(maxx-minx)*(maxy-miny)<<endl);
      return (maxx-minx)*(maxy-miny);
    }
    if (area(minx,maxx, miny,maxy, i.x,i.y,i.r)>1e-9L){
      any=true;
    }
  }
  if (not any) return 0;
  if (c.size()==1){
    DEBUGV(cerr<<"    area "<<minx<<" "<<maxx<<" | "<<miny<<" "<<maxy<<" | "<<c[0].x<<" "<<c[0].y<<" "<<c[0].r
        <<" = "<<area(minx,maxx, miny,maxy, c[0].x,c[0].y,c[0].r)<<endl);
    return area(minx,maxx, miny,maxy, c[0].x,c[0].y,c[0].r);
  }
  if (depth>=30) return 0.L;

  ld const xs[3]={minx,(minx+maxx)/2,maxx};
  ld const ys[3]={miny,(miny+maxy)/2,maxy};
  vector<Circle> s[2][2];
  for (auto const &i: c)
    for (int u=2; u--;)
      for (int v=2; v--;)
        if (area(xs[u],xs[u+1], ys[v],ys[v+1], i.x,i.y,i.r)>1e-6L)
          s[u][v].push_back(i);
  ld res=0;
  for (int u=2; u--;)
    for (int v=2; v--;){
      ld tmp=solve(s[u][v], xs[u],xs[u+1], ys[v],ys[v+1], depth+1);
      if (depth==0)
      DEBUGV(cerr<<" sol "<<xs[u]<<"..."<<xs[u+1]<<" | "<<ys[v]<<"..."<<ys[v+1]<<" = "<<tmp<<endl);
      res+=tmp;
    }
  return res;
}

ld total_area(vector<ld> cx,vector<ld> cy,vector<ld> cr){
  vector<Circle> c;
  for (int i=cx.size(); i--;){
    DEBUGV(cerr<<"  "<<cx[i]<<" "<<cy[i]<<" "<<cr[i]<<endl);
    bool ok=(cr[i]>1e-6L);
    for (int j=cx.size(); j--;) if (i!=j){
      if (cr[j]>=hypotl(cx[i]-cx[j],cy[i]-cy[j])+cr[i]){
        ok=false;
      }
    }
    if (ok){
      c.push_back({cx[i],cy[i],cr[i]});
    }else{
      swap(cx[i],cx.back()); cx.pop_back();
      swap(cy[i],cy.back()); cy.pop_back();
      swap(cr[i],cr.back()); cr.pop_back();
    }
  }
  DEBUGV(cerr<<"using "<<c.size()<<endl);
  return solve(c);
}

int main(){
  ld angle=3.45692586256L;

  cerr.precision(12);// cerr<<fixed;
  cout.precision(12); cout<<fixed;

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
  ld rgt=min_rad+sqrtl(area/M_PI)+20;
  for (int iter=50; iter--;){
    ld const mid=(lef+rgt)/2.L;

    vector<ld> tcr=cr;
    for (int i=0; i<n; i++) tcr[i]=max(mid-cr[i],0.L);
    ld const total=total_area(cx,cy,tcr);
    if (total<area){
      lef=mid;
    }else{
      rgt=mid;
    }
    DEBUG(cerr<<mid<<" -> "<<total<<endl);
    DEBUGV(cerr<<endl);
  }

  cout<<lef<<endl;
}

