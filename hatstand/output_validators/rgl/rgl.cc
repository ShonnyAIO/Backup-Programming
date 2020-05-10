#include <unordered_map>/*{{{*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;/*}}}*/

#include "validator.h"

vector<string> tokens(istream &from){
  vector<string> res;
  for (string s; from>>s; res.push_back(s));
  return res;
}

JudgeCode validate(
    istream &canonical_input,
    istream &canonical_output,
    istream &team_output){

  // Read input.
  uint64_t n,m; assert(canonical_input>>n>>m);
  assert(1 <= n and n <= 1'000'000ll);
  assert(1 <= m and m <= 1'000'000ll);
  vector<uint64_t> p(m);
  for (uint64_t i=0; i<m; i++){
    assert(canonical_input>>p[i]);
  }

  // Read answers.
  auto const judge_tokens=tokens(canonical_output);
  auto const team_tokens=tokens(team_output);

  if (team_tokens.size() < judge_tokens.size()){
    cout<<"team output too few tokens."<<endl;
    return wrong_answer;
  }
  bool const same_answer = (judge_tokens[0] == team_tokens[0]);
  if (not same_answer){
    cout<<"team has a different answer from judge: "
        <<team_tokens[0]
        <<" vs "
        <<judge_tokens[0]
        <<"."<<endl;
  }

  uint64_t judge_answer=0;
  {
    stringstream sst(judge_tokens[0]);
    assert(sst>>judge_answer);
  }
  uint64_t team_answer=0;
  {
    stringstream sst(team_tokens[0]);
    if (not (sst>>team_answer)){
      cout<<"team answer is not a number: "<<team_tokens[0]<<endl;
      return wrong_answer;
    }
  }

  map<uint64_t,uint64_t> team_places;
  team_places[p[0]]=0;
  for (uint64_t i=0; i+1<n; i++){
    uint64_t x=0;
    {
      if (team_tokens.size()<=i+1){
        cout<<"team output too few tokens."<<endl;
        return wrong_answer;
      }
      stringstream sst(team_tokens[i+1]);
      if (not (sst>>x)){
        cout<<"team output invalid number: "<<team_tokens[i+1]<<endl;
        return wrong_answer;
      }
    }
    if (x < 1 or x > n){
      cout<<"team output invalid number: "<<x<<"."<<endl;
      return wrong_answer;
    }
    if (team_places.count(x)){
      cout<<"team output same number twice: "<<x<<"."<<endl;
      return wrong_answer;
    }
    team_places[x]=i;
  }

  uint64_t cost=0;
  for (uint64_t i=1; i<m; i++){
    if (p[i]!=p[i-1]){
      cost+=1+team_places[p[i]];
      swap(team_places[p[i]], team_places[p[i-1]]);
    }
  }
  if (cost!=team_answer){
    cout<<"team output wrong cost"<<endl;
    cout<<"  output team cost: "<<team_answer<<endl;
    cout<<"    real team cost: "<<cost<<endl;
    cout<<"         jury cost: "<<judge_answer<<endl;
    return wrong_answer;
  }
  if (cost!=judge_answer){
    if (cost<judge_answer){
      cout<<"team beat jury solution"<<endl;
      cout<<"  team cost: "<<cost<<endl;
      cout<<"  jury cost: "<<judge_answer<<endl;
      return judge_error;
    }else{
      cout<<"team did worse than jury solution"<<endl;
      cout<<"  team cost: "<<cost<<endl;
      cout<<"  jury cost: "<<judge_answer<<endl;
      return wrong_answer;
    }
  }else if (not same_answer){
    return wrong_answer;
  }else{
    return correct;
  }
}
