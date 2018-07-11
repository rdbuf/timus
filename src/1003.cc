#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <string>
#include <utility>
#include <functional>
using namespace std;

enum Parity { even, odd };

int main() {
	// we only then know for sure when we have the same segment covered in exact two times
	// thus, at each step we join the new segment with the already existent ones and check for twins with different parity
	int n, m;
	while (cin >> n >> m) {
		int steps = 0;
		unordered_map<int, vector<pair<int, Parity>>> by_l, by_r; // use unordered_map<int, map<Parity>> with exchange()
		for ( ; steps < m; ++steps) {
			int l, r; string str_parity;
			cin >> l >> r >> str_parity;
			if (l > n || r > n) goto exit;
			Parity parity = (str_parity == "even" ? even : odd);

			vector<pair<int, pair<int, Parity>>> newly_created;
			by_l[l].push_back({r, parity}), by_r[r].push_back({l, parity});
			newly_created.push_back({l, {r, parity}});
			for (auto& x : by_r[l - 1]) {
				by_l[x.first].push_back({r, Parity((x.second + parity) % 2)});
				by_r[r].push_back({x.first, Parity((x.second + parity) % 2)});
				newly_created.push_back({x.first, {r, Parity((x.second + parity) % 2)}});
				for (auto& y : by_l[r + 1]) {
					by_l[x.first].push_back({y.first, Parity((x.second + parity + y.second) % 2)});
					by_r[y.first].push_back({x.first, Parity((x.second + parity + y.second) % 2)});
					newly_created.push_back({x.first, {y.first, Parity((x.second + parity + y.second) % 2)}});
				}
			}
			for (auto& x : by_l[r + 1]) {
				by_r[x.first].push_back({l, Parity((x.second + parity) % 2)});
				by_l[l].push_back({x.first, Parity((x.second + parity) % 2)});
				newly_created.push_back({l, {x.first, Parity((x.second + parity) % 2)}});
				for (auto& y : by_r[l - 1]) {
					by_l[y.first].push_back({x.first, Parity((x.second + parity + y.second) % 2)});
					by_r[x.first].push_back({y.first, Parity((x.second + parity + y.second) % 2)});
					newly_created.push_back({y.first, {x.first, Parity((x.second + parity + y.second) % 2)}});
				}
			}
			// we should check only the newly created segments
			for (auto& seg1 : newly_created) {
				for (auto& seg2 : by_l[seg1.first]) {
					if (seg2.first == seg1.second.first && seg2.second != seg1.second.second) goto exit;
				}
				for (auto& seg2 : by_r[seg1.second.first]) {
					if (seg2.first == seg1.first && seg2.second != seg1.second.second) goto exit;
				}
			}
		}
	exit:
		cout << steps << "\n";
		string dummy;
		for (int i = steps; i < m; ++i) getline(cin, dummy);
	}
}