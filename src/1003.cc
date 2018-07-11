#include <iostream>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <cstdint>
using namespace std;

struct Parity {
	bool value;
	bool initialized = false;
	Parity() = default;
	constexpr Parity(bool a) : value(a), initialized(true) {}
	constexpr Parity operator+(Parity rhs) const { assert(rhs.initialized); return Parity(initialized ? value ^ rhs.value : rhs.value); }
	constexpr bool operator==(Parity rhs) const { return (initialized ? rhs.value == value : true); }
	constexpr bool operator!=(Parity rhs) const { return !(*this == rhs); }
};
constexpr static Parity even(0), odd(1);

int main() {
	// we only then know for sure when we have the same segment covered in exact two times
	// thus, at each step we join the new segment with the already existent ones and check for twins with different parity
	int n, m;
	while (cin >> n >> m) {
		int steps = 0;
		unordered_map<uint32_t, unordered_map<uint32_t, Parity>> straight, reverse; // segments
		for ( ; steps < m; ++steps) {
			uint32_t l, r; string str_parity; cin >> l >> r >> str_parity;
			if (l > n || r > n) goto exit;
			Parity parity = (str_parity == "even" ? even : odd);

			if (exchange(straight[l][r], parity) != parity) goto exit;
			if (exchange(reverse[r][l], parity) != parity) goto exit;
			for (const auto& x : reverse[l - 1]) {
				const auto& newseg_l = x.first, & newseg_r = r; const auto newseg_parity = x.second + parity;
				if (exchange(straight[newseg_l][newseg_r], newseg_parity) != newseg_parity) goto exit;
				if (exchange(reverse[newseg_r][newseg_l], newseg_parity) != newseg_parity) goto exit;
				for (const auto& y : straight[r + 1]) {
					const auto& newseg_r = y.first; const auto newseg_parity = (x.second + parity) + y.second;
					if (exchange(straight[newseg_l][newseg_r], newseg_parity) != newseg_parity) goto exit;
					if (exchange(reverse[newseg_r][newseg_l], newseg_parity) != newseg_parity) goto exit;
				}
			}
			for (const auto& x : straight[r + 1]) {
				const auto& newseg_l = l, & newseg_r = x.first; const auto newseg_parity = parity + x.second;
				if (exchange(straight[newseg_l][newseg_r], newseg_parity) != newseg_parity) goto exit;
				if (exchange(reverse[newseg_r][newseg_l], newseg_parity) != newseg_parity) goto exit;
				for (const auto& y : reverse[l - 1]) {
					const auto& newseg_l = y.first; const auto newseg_parity = y.second + (parity + x.second);
					if (exchange(straight[newseg_l][newseg_r], newseg_parity) != newseg_parity) goto exit;
					if (exchange(reverse[newseg_r][newseg_l], newseg_parity) != newseg_parity) goto exit;
				}
			}
		}
	exit:
		cout << steps << "\n";
		string dummy; for (int i = steps; i < m; ++i) getline(cin, dummy);
	}
}