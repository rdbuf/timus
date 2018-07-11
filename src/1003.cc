#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <utility>
#include <functional>
#include <cstdint>
using namespace std;

int main() {
	// we only then know for sure when we have the same segment covered in exact two times
	// thus, at each step we join the new segment with the already existent ones and check for twins with different parity

	// all we need to keep track of the segments is a map: l -> (r, parity) since
	// if we have several segments starting at l, we can unambiguously transform them into a few adjacent segments
	// and otherwise we're already safe
	int n, m;
	while (cin >> n >> m) {
		unordered_map<uint32_t, uint32_t> segments; // [l; r) segments set
		unordered_map<uint32_t, bool> segment_parity;
		function<bool(uint32_t, uint32_t, bool)> insert_segment = [&](uint32_t l, uint32_t r, bool parity) -> bool { // returns the consistency
			if (segments.find(l) == segments.end()) {
				segments[l] = r, segment_parity[l] = parity;
				return true;
			}
			if (segments[l] == r) return segment_parity[l] == parity;
			if (segments[l] < r) parity ^= segment_parity[l];
			else segment_parity[l] = exchange(parity, parity ^ segment_parity[l]);
			if (segments[l] > r) swap(segments[l], r);
			return insert_segment(segments[l], r, parity);
		};
		int steps;
		for (steps = 0; steps < m; ++steps) {
			uint32_t l, r; string str_parity; cin >> l >> r >> str_parity;
			bool parity = str_parity == "odd";
			if (!insert_segment(l, r+1, parity)) goto exit;
		}
	exit:
		cout << steps << "\n";
		string dummy; for (int i = steps; i < m; ++i) getline(cin, dummy);
	}
}