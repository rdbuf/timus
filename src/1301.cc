#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

struct Ticket { int cost, len; };
int main() {
	Ticket tickets[3];
	for (auto& x : tickets) cin >> x.len;
	for (auto& x : tickets) cin >> x.cost;
	int n; cin >> n;
	int a, b; cin >> a >> b; a -= 1, b -= 1; if (a > b) swap(a, b);
	vector<int> distances(n); for (int i = 1; i < n; ++i) cin >> distances[i];

	vector<uint64_t> dp(n, numeric_limits<uint64_t>::max());
	dp[a] = 0;
	for (int i = a + 1; i <= b; ++i) {
		for (int j = i - 1; j >= a && distances[i] - distances[j] <= tickets[2].len; --j) {
			for (const auto& ticket : tickets) {
				if (distances[i] - distances[j] <= ticket.len) {
					dp[i] = min(dp[i], dp[j] + ticket.cost);
					goto prev;
				}
			}
			prev: {}
		}
	}
	cout << dp[b];
}