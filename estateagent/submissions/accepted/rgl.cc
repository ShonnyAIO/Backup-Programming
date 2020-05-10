#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> cost;
int n;

namespace hungary{
  int assignment_cost(vector<int> const &assignment);
  vector<int> max_cost_assignment();
}

int main(){
  int m;
  cin>>n>>m;
  cost.assign(n,vector<int>(n,-(1<<21)));

  for (int i=0; i<n; i++){
    cost[i][i]=0;
  }
  for (int i=0; i<m; i++){
    int a,b,c; cin>>a>>b>>c;
    cost[--a][--b]=c;
  }

  cout.precision(2);
  cout<<fixed<<hungary::assignment_cost(hungary::max_cost_assignment())*0.05L<<endl;
}

namespace hungary{
  int assignment_cost(vector<int> const &assignment){
    int total=0;
    for (auto i=assignment.size(); i--!=0;) total+=cost[i][assignment[i]];
    return total;
  }

  void compute_slack(int const x, vector<int> &slack, vector<int> &slackx, vector<int> &lx, vector<int> &ly){
    for (int y = 0; y < n; ++y){
      if (lx[x] + ly[y] - cost[x][y] < slack[y]){
        slack[y] = lx[x] + ly[y] - cost[x][y];
        slackx[y] = x;
      }
    }
  }

  vector<int> max_cost_assignment(){
    vector<int> xy(n,-1),yx(n,-1);
    vector<int> lx(n,numeric_limits<int>::min()),ly(n);
    for (int i=n; i--;)
      for (int j=n; j--;)
        lx[i]=max(lx[i],cost[i][j]);

    for (int match_size=0; match_size<n; match_size++){
      deque<int> q;

      vector<int> S(n,0),T(n,0);
      vector<int> slack(n,numeric_limits<int>::max()),slackx(n);
      vector<int> aug_path(n,-1);

      for (int x=0; x<n; x++)
        if (xy[x]==-1){
          q.push_back(x);
          S[x]=true;
          compute_slack(x,slack,slackx,lx,ly);
          break;
        }

      int x_start = 0;
      int y_start = 0;

      for (bool found_augmenting_path=false; not found_augmenting_path;){
        while (q.size()>0 && !found_augmenting_path){
          int const x = q.front(); q.pop_front();
          for (int y=0; y<n; ++y){
            if (cost[x][y]==lx[x]+ly[y] and not T[y]){
              if (yx[y]==-1){
                y_start=y, x_start=x;
                found_augmenting_path=true;
                break;
              }

              T[y]=true;
              q.push_back(yx[y]);

              aug_path[yx[y]]=x;
              S[yx[y]]=true;
              compute_slack(yx[y],slack,slackx,lx,ly);
            }
          }
        }

        if (found_augmenting_path)
          break;

        int delta = numeric_limits<int>::max();
        for (unsigned int i=0; i<T.size(); ++i)
          if (!T[i])
            delta=min(delta,slack[i]);

        for (unsigned int i = 0; i < T.size(); ++i){
          if (S[i]) lx[i] -= delta;
          if (T[i]) ly[i] += delta; else slack[i] -= delta;
        }

        q.clear();
        for (int y=0; y<n; ++y){
          if (!T[y] && slack[y]==0){
            if (yx[y] == -1){
              x_start = slackx[y];
              y_start = y;
              found_augmenting_path = true;
              break;
            }else{
              T[y] = true;
              if (!S[yx[y]]){
                q.push_back(yx[y]);

                aug_path[yx[y]] = slackx[y];
                S[yx[y]] = true;
                compute_slack(yx[y], slack, slackx, lx, ly);
              }
            }
          }
        }
      }

      for (int cx=x_start, cy=y_start, ty; cx!=-1; cx=aug_path[cx], cy=ty){
        ty = xy[cx];
        yx[cy] = cx;
        xy[cx] = cy;
      }
    }
    return xy;
  }
}
