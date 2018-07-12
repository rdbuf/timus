#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <memory>
using namespace std;

struct Cell { int hor, ver, posdiag, negdiag, result; };

int main() {
	int n; cin >> n;
	vector<vector<char>> a(n, vector<char>(n));
	for (auto& x : a) for (auto& y : x) { char tmp; cin >> tmp; y = tmp == 's'; }
	vector<vector<unique_ptr<array<Cell, 2>>>> dp(n); for (auto& x : dp) x = vector<unique_ptr<array<Cell, 2>>>(n);

	for (int s = 0; s < 2 * n - 1; ++s) {
		for (int i = 0; i <= s; ++i) {
			int j = s - i; if (i >= n || j >= n) continue;
			int idx = a[i][j]; dp[i][j] = make_unique<array<Cell, 2>>();
			(*dp[i][j])[idx].hor = (j > 0 ? (*dp[i][j-1])[idx].hor : 0) + 1;
			(*dp[i][j])[idx].ver = (i > 0 ? (*dp[i-1][j])[idx].ver : 0) + 1;
			(*dp[i][j])[idx].posdiag = (i > 0 && j < n-1 ? (*dp[i-1][j+1])[idx].posdiag : 0) + 1;
			(*dp[i][j])[idx].negdiag = (i > 0 && j > 0 ? (*dp[i-1][j-1])[idx].negdiag : 0) + 1;
			(*dp[i][j])[idx].result = max({
				(j > 0 ? (*dp[i][j-1])[idx].result : 0),
				(i > 0 ? (*dp[i-1][j])[idx].result : 0),
				(i > 0 && j < n-1 ? (*dp[i-1][j+1])[idx].result : 0),
				(i > 0 && j > 0 ? (*dp[i-1][j-1])[idx].result : 0),
				(*dp[i][j])[idx].hor,
				(*dp[i][j])[idx].ver,
				(*dp[i][j])[idx].posdiag,
				(*dp[i][j])[idx].negdiag
			});
			(*dp[i][j])[!idx].result = max({
				(j > 0 ? (*dp[i][j-1])[!idx].result : 0),
				(i > 0 ? (*dp[i-1][j])[!idx].result : 0),
				(i > 0 && j < n-1 ? (*dp[i-1][j+1])[!idx].result : 0),
				(i > 0 && j > 0 ? (*dp[i-1][j-1])[!idx].result : 0)
			});
		}

		for (int i = 0; i <= s - 2; ++i) {
			int j = s - 2 - i; if (i >= n || j >= n) continue;
			dp[i][j].release();
		}
	}

	auto S = (*dp[n-1][n-1])[0].result, s = (*dp[n-1][n-1])[1].result;
	if (s > S) cout << "s\n" << s;
	else if (s < S) cout << "S\n" << S;
	else cout << "?\n" << s;
}