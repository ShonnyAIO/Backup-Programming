#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector< pair < int, int > > get_mask_order(int b) {
    if (b == 1) {
        return vector< pair < int, int > >{ {0, -1}, {1, 0} };
    }
    auto res = get_mask_order(b - 1);
    res.resize(1 << b);
    for (int i = 0; i < (1 << (b - 1)); ++i) {
        res[i].first = res[i].first << 1;
        res[i].second = res[i].second + 1;
    }
    for (int i = 0; i < (1 << (b - 1)); ++i) {
        res[(1 << b) - i - 1].first = res[i].first | 1;
        res[(1 << b) - i - 1].second = res[i + 1].second;
    }
    res[0].second = -1;
    res[1 << (b - 1)].second = 0;
    return res;
// 00 0 -1 -1
// 01 0  0  1
// 11 0  1  2
// 10 0  0  1
// 
// 10 1     0
// 11 1     1
// 01 1     2
// 00 1     1

}

// hacky
int half = 0;
vector< int > nones;
vector< vector < vector < int > > > diff_per_mask(2);
bool cmp(int m1, int m2) {
    return diff_per_mask[half][m1] < diff_per_mask[half][m2] ||
        diff_per_mask[half][m1] == diff_per_mask[half][m2] && nones[m1] > nones[m2];
}

int main() {
    int n, m, nc;
    cin >> n >> m >> nc;
    if (nc == 1) {
        cout << n << '\n';
        return 0;
    }

    auto diff_by_row = vector< vector< int > > (n, vector< int >(nc - 1, 0));

    for (int i = 0; i < n; ++i) {
        vector< int > counts(nc);
        for (int j = 0; j < m; ++j) {
            int c;
            cin >> c;
            counts[c - 1] ++;
        }
        for (int c = 0; c < nc - 1; ++c) {
            diff_by_row[i][c] = counts[c] - counts[nc - 1];
        }

        // for (int c = 0; c < nc - 1; ++c) {
        //     cerr << diff_by_row[i][c] << ' ';
        // }
        // cerr << '\n';
    }

    vector< vector< int > > sorted_mask(2);
    nones = vector< int > ((1 << ((n + 1) / 2)), 0);
    for (int mask = 0; mask < (1 << ((n + 1) / 2)); ++mask) {

        for (int m = mask; m > 0; m >>= 1) {
            nones[mask] += (m & 1);
        }
    }


    half = 0;
    for (int r1 = 0; r1 < n; r1 += (n + 1) / 2, half += 1) {
        int r2 = min(r1 + (n + 1) / 2, n);
        int dr = r2 - r1;

        diff_per_mask[half] = vector< vector< int > >(1 << dr);

        vector< pair< int, int > > mask_order = get_mask_order(dr);

        // for (int i = 0; i < (1 << dr); ++i) {
        //     cerr << mask_order[i].first << ' ' << mask_order[i].second << '\n';
        // }
        // cerr << '\n';

        vector< int > diff(nc - 1, 0);

        int coef = 1;
        if (half == 1) {
            coef *= -1;
        }

        for (auto mask_ind : mask_order) {
            int mask = mask_ind.first;
            int ind  = mask_ind.second;
            if (ind == -1) { // the first one
                for (int i = 0; i < dr; ++i) {
                    if ((mask >> i) & 1) {
                        for (int c = 0; c < nc - 1; ++c) {
                            diff[c] = diff[c] + coef * diff_by_row[i + r1][c];
                        }
                    }
                }
            } else {
                int here = coef;
                if ((mask & (1 << ind)) == 0) {
                    here *= -1;
                }
                for (int c = 0; c < nc - 1; ++c) {
                    diff[c] = diff[c] + here * diff_by_row[ind + r1][c];
                }
            }
            diff_per_mask[half][mask] = diff;
        }

        // for (int mask = 0; mask < (1 << dr); ++mask) {
        //     for (int c = 0; c < nc - 1; ++c) {
        //         fprintf(stderr, "%2d", diff_per_mask[half][mask][c]);
        //     }
        //     cerr << '\n';
        // }
        // cerr << endl;

        sorted_mask[half].resize(1 << dr);
        for (int i = 0; i < (1 << dr); ++i) {
            sorted_mask[half][i] = i;
        }

        sort(sorted_mask[half].begin(), sorted_mask[half].end(), cmp);
    }

    // for (auto v : sorted_mask) {
    //     for (auto m : v) {
    //         cerr << m << ' ';
    //     }
    //     cerr << '\n';
    // }

    int j = 0;
    int answer = 0;
    for (int i = 0; i < sorted_mask[0].size(); ++i) {
        int m1 = sorted_mask[0][i];
        while (j < sorted_mask[1].size()) {
            int m2 = sorted_mask[1][j];
            if (diff_per_mask[1][m2] > diff_per_mask[0][m1]) {
                break;
            }
            if (diff_per_mask[1][m2] == diff_per_mask[0][m1]) {
                if (answer < nones[m1] + nones[m2]) {
                    answer = nones[m1] + nones[m2];
                    // cerr << m1 << ' ' << m2 << '\n';
                }
            }
            j++;
        }
    }
    cout << answer << '\n';
    return 0;
}

