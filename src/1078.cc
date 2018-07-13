#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment { int left, right, idx; };
bool encloses(const Segment& a, const Segment& b) { return a.left < b.left && a.right > b.right; }
int len(const Segment& a) { return a.right - a.left; }

int main() {
	int n; cin >> n;
	vector<Segment> a(n); for (int i = 0; i < n; ++i) cin >> a[i].left >> a[i].right, a[i].idx = i;
	sort(a.begin(), a.end(), [](auto& a, auto& b) { return len(a) < len(b); });

	vector<vector<int>> dp(n); // could just store (prev, size) but it's already efficient enough
	dp[0] = {a[0].idx};
	for (int i = 1; i < n; ++i) {
		for (int j = i - 1; j != -1; --j) {
			if (encloses(a[i], a[j]) && dp[j].size() > dp[i].size()) dp[i] = dp[j];
		}
		dp[i].push_back(a[i].idx);
	}
	const auto& answer = *max_element(dp.begin(), dp.end(), [](const auto& a, const auto& b) { return a.size() < b.size(); });
	cout << answer.size() << "\n"; for (auto& x : answer) cout << x + 1 << " "; cout << endl;
}