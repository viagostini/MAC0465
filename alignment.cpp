#include <cstdio>
#include <string>
#include <cassert>

using namespace std;

string s = "AAAC";
string t = "AGC";

string align_s = "";
string align_t = "";

int dp[100][100];

void align (int i, int j) {
    if (i == 0 && j == 0)
        return;

    if (i > 0 && dp[i][j] == dp[i-1][j] - 2) {
        align(i-1, j);
        align_s += s[i-1];
        align_t += '-';
    }
    else if (i > 0 && j > 0) {
        int match = (s[i-1] == t[j-1]) ? 1 : -1;
        if (dp[i][j] == dp[i-1][j-1] + match) {
            align(i-1, j-1);
            align_s += s[i-1];
            align_t += t[j-1];
        } 
    }
    else {
        align(i, j-1);
        align_s += '-';
        align_t += t[j-1];
    }
}

int sim_dp (int n, int m) {
    for (int i = 0; i <= n; i++)
        dp[i][0] = -2 * i;
  
    for (int j = 0; j <= m; j++)
        dp[0][j] = -2 * j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int match = (s[i-1] == t[j-1]) ? 1 : -1;
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]) - 2;
            dp[i][j] = max(dp[i][j], dp[i-1][j-1] + match);
        }
    }
    return dp[n][m];
}

int sim (int i, int j) {
    if (dp[i][j] == 0) {
        if (i == 0 || j == 0) {
            dp[i][j] = -2 * max(i,j);
        } 
        else {
            int match = (s[i-1] == t[j-1]) ? 1 : -1;
            dp[i][j] = max(sim(i-1,j), sim(i, j-1)) - 2;
            dp[i][j] = max(dp[i][j], sim(i-1, j-1) + match);
        }
  }
  return dp[i][j];
}

int main() {
    int x = sim(s.size(), t.size());
    int y = sim_dp(s.size(), t.size());
    assert(x == y);
    align(s.size(), t.size());
    printf("%s\n%s\n", align_s.c_str(), align_t.c_str());
    printf("Similarity = %d\n", x);
}
