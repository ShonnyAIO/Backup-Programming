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

using namespace std;
typedef long long ll;

enum JudgeCode:int{
  judge_error=1,
  correct=42,
  wrong_answer=43,
};

vector<set<int>> read_answer(
    istream &in,
    int const group_size,
    map<int,int> allowed_digits,
    JudgeCode failure_code){

  vector<string> buffer;
  for (string s; in>>s;){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    buffer.emplace_back(s);
  }
  if (buffer.size()==1 and buffer[0]=="impossible"){
    return {};
  }

  if (buffer.size()%group_size){
    cout<<"Wrong number of tokens output: "<<buffer.size()<<" is not a multiple of "<<group_size<<endl;
    exit(failure_code);
  }

  vector<set<int>> res;
  for (int i=0; i<buffer.size(); i++){
    stringstream sst(buffer[i]);
    int x;
    if (not (sst>>x)){
      cout<<"Token "<<i+1<<" in input ("<<buffer[i]<<") is not a number"<<endl;
      exit(failure_code);
    }
    if (not (1 <= x and x <= 1000000)){
      cout<<"Input "<<x<<" is not an integer within bounds"<<endl;
      exit(failure_code);
    }
    if (not (allowed_digits[x]--)){
      cout<<"Used "<<x<<" too many times"<<endl;
      exit(failure_code);
    }
    if (i%group_size==0){
      res.emplace_back();
    }
    if (not res[i/group_size].insert(x).second){
      cout<<"Used "<<x<<" more than once in row "<<(i/group_size+1)<<endl;
      exit(failure_code);
    }
  }

  return res;
}

int main(int argc,char **argv){
  if (argc<3){
    cerr<<"usage: "<<argv[0]<<" testcase.in testcase.ans [feedback]< team.out"<<endl;
    return judge_error;
  }
  else if (argc>3){
    assert(freopen((string(argv[3])+"/feedback.txt").c_str(),"w",stdout));
  }
  else if (argc>4){
    cerr<<"warning: ignoring "<<argc-4<<" extra arguments"<<endl;
  }
  ifstream canonical_input(argv[1]);
  ifstream canonical_output(argv[2]);
  auto &team_output = cin;

  // Read input.
  size_t n,x; assert(canonical_input>>n>>x);
  assert(1 <= n and n <= 1000000);
  assert(1 <= x and x <= n);

  map<int,int> allowed_digits;
  for (int i=0; i<n; i++){
    int v; assert(canonical_input>>v);
    assert(1 <= v and v <= 1000000);
    allowed_digits[v]++;
  }

  // Read expected and team answers.
  auto const expect = read_answer(canonical_output, x, allowed_digits, judge_error);
  auto const team = read_answer(team_output, x, allowed_digits, wrong_answer);

  if (expect.empty()){
    if (team.empty()){
      return correct;
    }else{
      cout<<"Team found a solution, but we didn't!"<<endl;
      return judge_error;
    }
  }else{
    cerr<<"sizes are "<<expect.size()<<" "<<team.size()<<endl;
    if (team.empty()){
      cout<<"We found a solution, but team didn't"<<endl;
      return wrong_answer;
    }else if (expect.size()==team.size()){
      return correct;
    }else if (expect.size()<team.size()){
      cout<<"We found a solution ("<<expect.size()<<" tokens), but team's is better ("<<team.size()<<" tokens)!"<<endl;
      return judge_error;
    }else{
      cout<<"Team found a solution ("<<team.size()<<" tokens), but ours is better ("<<expect.size()<<" tokens)"<<endl;
      return wrong_answer;
    }
  }
}
