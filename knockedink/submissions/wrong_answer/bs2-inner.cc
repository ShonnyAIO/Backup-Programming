#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

/**
 * Implementation from: https://www.cnblogs.com/oyking/p/3424999.html
 */

const int maxn = 1005;
typedef double db;
const db EPS = 1e-6;
typedef pair<db, db> PDD;
ld x[ maxn ], y[ maxn ], r[ maxn ];
ld nx[ maxn ], ny[ maxn ], nr[ maxn ];
ld xl[ maxn ], xr[ maxn ];

int s[ maxn ];
inline bool cmp( int a, int b) {
     if( x[ a ] - r [ a ] == x[ b ] - r [ b ] ) return x[ a ] + r[ a ] < x[ b ] + r [ b ];
     return x[ a ] - r[ a ] < x[ b ] - r [ b ];
}
inline bool cmp0(int a, int b){return r[ a ] > r [ b ];}
int n;
int L, R;
PDD se[ maxn ];
inline db f( db v){
   int sz = 0, i, j ;
   db ret = 0.0;
   for(i = L; i < R; ++ i){
        if( v <= xl[ i ] || v >= xr[ i ] ) continue;
        j = s[ i ];
        db d = sqrt(r[ j ]- (v - x [ j ]) * (v - x[ j ]));
        se[ sz ].first = y[ j ] - d;
        se[ sz ].second = y[ j ] +  d;
        ++ sz;
   }
   sort( se, se + sz);
   for(i = 0; i < sz; ++ i){
         db nowl , nowr;
         nowl = se[ i ].first;
         nowr = se[ i ].second;
         for( j = i + 1; j < sz; ++ j) if(se[ j ].first > nowr) break;
         else nowr = max( nowr, se[ j ].second);
         ret += nowr - nowl;
         i = j - 1;
   }
   return ret;
}
inline db rsimp( db l,db m, db r, db sl, db sm, db sr,db tot){
  db m1 = (l + m) * 0.5, m2 = (m + r) * 0.5;
  db s0 = f( m1), s2 = f( m2);
  db gl = (sl + sm + s0 + s0 + s0 + s0)*(m-l), gr = (sm + sr + s2 + s2 + s2 + s2)*(r-m);
  if( abs(gl + gr - tot) < EPS) return gl + gr;
  return rsimp( l, m1, m, sl, s0, sm, gl) + rsimp( m, m2,r, sm, s2, sr, gr);
}

ld area_of_circles(){
  sort( s, s + n, cmp) ;
  db lo, hi, ans = 0.0;
  int i, j;
  for(i = 0; i < n; ++ i) xl[ i ] = x[ s[ i ] ] - r[ s[ i ] ], xr[ i ] = x[ s[ i ] ] + r[ s[ i ] ], r[ s[i] ] *= r[ s[i] ];
  for(i = 0; i < n; ++ i){
    ld ilo, ihi;
    ilo = xl[ i ];
    ihi = xr[ i ];
    for(j = i + 1; j < n; ++ j) {
          if( xl[ j ] > ihi ) break;
          ihi = max( ihi, xr[ j ]);
    }
    db lo = ilo;
    db hi = ihi;
    L = i;
    R = j;
    db mid = (lo + hi) * 0.5;
    db sl = f(lo), sm = f(mid), sr = f(hi);
    db tot = sl + sr + sm + sm + sm + sm;
    ans += rsimp( lo, mid , hi, sl, sm , sr, tot );
    i = j - 1;
  }
  return ans/6.L;
}

ld total_area(vector<ld> cx,vector<ld> cy,vector<ld> cr){
  n=cx.size();
  for (int i=0; i<n; i++) x[i]=cx[i], y[i]=cy[i], r[i]=cr[i], s[i]=i;
  sort(s,s+n,cmp0);
  int j=0,k=0;
  for (int i=0; i<n; i++){
    for (k=0; k<j; k++)
      if( (nx [ k ] - x [s[i]]) * (nx [ k ] - x [s[i]])  + (ny [ k ] - y [s[i]]) *(ny [ k ] - y [s[i]])
                     <= (nr[ k ] - r[ s[ i ] ]) * (nr[ k ] - r[ s[ i ] ]) ) break;
    if (k==j){
      nx[j]=x[s[i]];
      ny[j]=y[s[i]];
      nr[j]=r[s[i]];
      s[j]=j;
      j++;
    }
  }

  return area_of_circles();
}

int main(){
  ld angle=2.45692586256L;

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
  cout<<fixed<<lef-min_rad<<endl;
}

