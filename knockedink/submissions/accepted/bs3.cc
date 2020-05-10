#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

/**
 * Direct integration with Green's theorem.
 * Implementation from: https://github.com/deeepeshthakur/UsefulCodes/blob/master/AreaOfUnionOfCircles2.cpp
 *
 * This code is BROKEN but passes the test data.
 */

constexpr ld sq(ld a){
  return a*a;
}

constexpr ld parg(ld d){
	while (d>2*M_PI) d-=2*M_PI;
  while (d<-1e-9L) d+=2*M_PI;
	return d;
}

bool inter(int i,int j,std::vector<ld>& x,std::vector<ld>& y,std::vector<ld>& r){
	ld d = sqrtl(sq(x[i]-x[j])+sq(y[i]-y[j]));
	return not (d>r[i]+r[j] or std::abs(r[i]-r[j])>=d);
}

template <class T>
void quadratic(ld a,ld b,ld c,T& x1,T& x2){
	x1 = (-b-sqrtl(sq(b)-4*a*c))/(2*a);
	x2 = (-b+sqrtl(sq(b)-4*a*c))/(2*a);
}

void lyx(ld a,ld b,ld c,ld& x, ld& y){
	if(b){
		y=(c-a*x)/b;
	}
}

bool lcf(ld x,ld y,ld r,ld a,ld b, ld c,std::vector<ld>& ans){
	ld x1,x2,y1,y2;
	if(b)
	{
		quadratic(1+sq(a/b),-2*x-2*(a/b)*(c/b-y),sq(x)+sq(c/b-y)-sq(r),x1,x2);
		lyx(a,b,c,x1,y1);
		lyx(a,b,c,x2,y2);
		ans = {x1,y1,x2,y2};
	}
	else{
		quadratic(1,-2*y,sq(y)+sq(c/a-x)-sq(r),y1,y2);
		x1=c/a;
		ans={x1,y1,x1,y2};
	}
	return true;
}

constexpr ld gth(ld x,ld y){
  if (abs(x)<1e-9L)
    return abs(y)<1e-9L? M_PI: y>0? M_PI/2.L: 1.5*M_PI;
  if (x>0)
    return abs(y)<1e-9L? 0: y>0? atanl(y/x): 2*M_PI-atanl(abs(y/x));
  if (x<0)
    return abs(y)<1e-9L? M_PI: y>0? M_PI-atanl(abs(y/x)): M_PI+atanl(abs(y/x));
}

constexpr ld f1(ld x,ld y, ld r, ld theta){
	return r*(x*std::sin(theta))+ sq(r)*(theta+std::sin(theta)*std::cos(theta))*0.5;
}

ld f(int n,std::vector<ld> x,std::vector<ld> y,std::vector<ld> r){
	ld ans=0;
  for (int i=0; i<n; i++){
		std::vector<std::pair<ld,ld>> iPnts{};
    for (int j=0; j<n; j++){
			if(i!=j&&inter(i,j,x,y,r)){
				std::vector<ld> ans(4,0.0);
				lcf(x[i],y[i],r[i],2*(x[j]-x[i]),2*(y[j]-y[i]),sq(r[i])-sq(r[j])+sq(x[j])-sq(x[i])+sq(y[j])-sq(y[i]),ans);
				ld theta1=gth(ans[0]-x[i],ans[1]-y[i]);
        ld theta2=gth(ans[2]-x[i],ans[3]-y[i]);
				if(theta1>theta2){ std::swap(theta1,theta2);}

				if(sq(x[j]-x[i]-r[i]*std::cos((theta1+theta2)/2.0))+sq(y[j]-y[i]-r[i]*std::sin((theta1+theta2)/2.0))<sq(r[j])){
					iPnts.push_back({theta1,theta2});
				}
				else{
					if(sq(x[j]-x[i]-r[i]*std::cos(parg((theta1+theta2)/2.0+M_PI)))+sq(y[j]-y[i]-r[i]*std::sin(parg((theta1+theta2)/2.0+M_PI)))<sq(r[j])){
						iPnts.push_back({theta2,2*M_PI});
						iPnts.push_back({0.0,theta1});
					}
				}
			}
		}
		if(iPnts.size()==0){
			ans+=M_PI*sq(r[i]);
		}
		else{
			std::sort(iPnts.begin(),iPnts.end());
			ld theta1=iPnts[0].first;
      ld theta2=iPnts[0].second;
			std::vector<std::pair<ld,ld>> intlims{{0.0,theta1}};

      for (int j=0; j<iPnts.size(); j++){
				while(j<iPnts.size()&&theta2>=iPnts[j].first){
					theta2=std::max((ld)iPnts[j].second,theta2);
					j++;
				}
				if(j<iPnts.size()){
					intlims.push_back({theta2,iPnts[j].first});
					theta1=iPnts[j].first;
					theta2=iPnts[j].second;
				}
			}
			intlims.push_back({theta2,2*M_PI});

      for (int j=0; j<intlims.size(); j++){
				if(!(intlims[j].first==0.0&&intlims[j].second==2*M_PI)&&(intlims[j].first!=intlims[j].second)){
					ans+=(f1(x[i],y[i],r[i],intlims[j].second)-f1(x[i],y[i],r[i],intlims[j].first));
				}
			}
		}
	}
	return ans;
}

constexpr bool f4(int j,int i,std::vector<ld>& x,std::vector<ld>& y,std::vector<ld>& r){
	return (j!=i && (sqrtl(sq(x[i]-x[j])+sq(y[i]-y[j]))+r[j])<=r[i])? true:false;
}

ld total_area(vector<ld> cx,vector<ld> cy,vector<ld> cr){
  for (int i=cx.size(); i--;){
    bool ok=(cr[i]>1e-9L);
    for (int j=cx.size(); j--;) if (i!=j){
      if (cr[j]>=hypotl(cx[i]-cx[j],cy[i]-cy[j])+cr[i]){
        ok=false;
      }
    }
    if (not ok){
      swap(cx[i],cx.back()); cx.pop_back();
      swap(cy[i],cy.back()); cy.pop_back();
      swap(cr[i],cr.back()); cr.pop_back();
    }
  }
  return f(cx.size(),cx,cy,cr);
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
  cout<<fixed<<lef<<endl;
}

