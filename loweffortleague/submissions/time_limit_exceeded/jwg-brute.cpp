#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

struct Bribe {
	int team;
	int skill;
	long long bribe;
	string losers; // for debugging.

	Bribe(int t, int s, long long  b, string l) : team(t), skill(s), bribe(b), losers(l){
	}
};

int team_bribe(int winner_skill, int loser_skill) {
	long long diff = max(loser_skill - winner_skill, 0);
	return diff * diff;
}

void add_or_replace(unordered_map<int,Bribe> &bribe_map, Bribe b) {
	auto got = bribe_map.find(b.team);
	if ( got == bribe_map.end() ) {
		bribe_map.insert({b.team, b});
	} else {
		if (got->second.bribe > b.bribe) {
			got->second = b;
		}
	}
}

vector<Bribe> calc_bribes(vector<int> t, int s, int e) {
	if (e - s > 1) {
		vector<Bribe> all_bribes;	

		vector<Bribe> left_bribes = calc_bribes(t, s, (s+e-1)/2);
		vector<Bribe> right_bribes = calc_bribes(t, (s+e+1)/2, e);

		unordered_map<int,Bribe> bribe_map;

		for(int i=0; i < left_bribes.size(); ++i) {
			for(int j=0; j < right_bribes.size(); ++j) {
				add_or_replace(bribe_map, Bribe(left_bribes[i].team, left_bribes[i].skill,
					team_bribe(left_bribes[i].skill, right_bribes[j].skill) + left_bribes[i].bribe + right_bribes[j].bribe, 
					left_bribes[i].losers + string(",") + to_string(right_bribes[j].team) + string("(") + right_bribes[j].losers + string(")")));
				if (s != 0) {
					add_or_replace(bribe_map, Bribe(right_bribes[j].team, right_bribes[j].skill, 
						team_bribe(right_bribes[j].skill, left_bribes[i].skill) + left_bribes[i].bribe +right_bribes[j].bribe, 
						right_bribes[j].losers + string(",") + to_string(left_bribes[i].team)+ string("(") + left_bribes[i].losers + string(")")));
				}
			}
		}
		for( auto it = bribe_map.begin(); it != bribe_map.end(); ++it ) {
          all_bribes.push_back( it->second );
        }
		return all_bribes;
	} else {
		//just two teams, actually work things out.
		if (s == 0) {
			return vector<Bribe> {Bribe(0, t[0], team_bribe(t[0], t[1]), "1")};
		} else {
			return vector<Bribe> {Bribe(s, t[s], team_bribe(t[s], t[s+1]), to_string(s+1)), Bribe(s+1, t[s+1], team_bribe(t[s+1], t[s]), to_string(s))};
		}
	}
}

int main(){
	int rounds; cin>>rounds;
	int team_count = 1<<rounds;

	vector<int> teams;
	// read in 2^n integers. Turn it into a binary.
	for(int i = 0; i < team_count; ++i) {
		int skill; cin>>skill;
		teams.push_back(skill);
	}
	// call a recursive function on all the teams.
	vector<Bribe> results = calc_bribes(teams, 0, team_count - 1);
	Bribe min_bribe = Bribe(-1, -1, 1ll<<50ll, "");
	for(int j =0; j < results.size(); ++j) {
		if (results[j].team == 0 && results[j].bribe < min_bribe.bribe) {
			min_bribe = results[j];
		}
	}
	cout<<min_bribe.bribe<<'\n';
	//cout<<"losers "<<min_bribe.losers<<'\n';
};
