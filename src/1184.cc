#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <vector>
using namespace std;

unsigned S(int D, vector<unsigned> a) {
	for (auto& x : a) x /= D;
	return accumulate(a.begin(), a.end(), 0);
}

int main() {
	int N, K; cin >> N >> K;
	vector<unsigned> a(N);
	for (auto& x : a) {
		double t; cin >> t; x = t * 100;
	}
	// maximum D of such nums that, dividing the numbers and summing it up, gives a num S: S >= K
	// 1 <= D <= 10000000 so no bruteforce
	// top bound for D: sum a / K -> max = 10000000 * 10000 / 1
	// lower bound of D: 1
	// using binsearch, we get max bound of num of ops = 37 * 10000, so let's try it
	int l = 1, r = *max_element(a.begin(), a.end());
	while (l < r) {
		const int D = (r + l) / 2;
		if (S(D, a) < K) r = D - 1;
		else l = D + 1;
	}
	int D = (l + r) / 2;
	while (++D, S(D, a) >= K) {}
	while (--D > 0 && S(D, a) < K) {}
	cout << fixed << setprecision(2) << double(D) / 100;
}