#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>
using namespace std;

int main() {
	uint64_t n, d; cin >> n >> d;
	vector<uint64_t> a(n);
	for (auto& x : a) cin >> x;
	// for each i such that a[i] > d, find a[i] - d closest capabilities to the left and account the distances
	uint64_t cost = 0;
	for (uint64_t i = 0; i < n; ++i) {
		uint64_t j = i - 1;
		while (a[i] > d && j != -1) {
			if (a[j] < d) {
				uint64_t transitioning = min(d - a[j], a[i] - d);
				cost += (i - j) * transitioning;
				a[i] -= transitioning;
				a[j] += transitioning;
			} else j -= 1;
		}
		a[i] = min(a[i], d);
	}
	cout << accumulate(a.begin(), a.end(), 0) << " " << cost;
}