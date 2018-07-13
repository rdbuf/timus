#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
	int n, m; cin >> n >> m;
	string msg; getline(cin, msg), getline(cin, msg);
	const size_t msg_size = msg.length();
	vector<int> a(msg_size+1, numeric_limits<int>::max());
	a[0] = 0;
	for (size_t i = 0; i < msg_size; ) {
		int range = max<int>(find_if_not(
				min(msg.end(), msg.begin() + i),
				min(msg.end(), msg.begin() + i + m),
				[](const char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' '; }
			) - min(msg.end(), msg.begin() + i), n);
		for (size_t j = i + 1; j < i + range + 1 && j < msg_size+1; ++j) a[j] = min(a[j], a[i] + 1);
		i += range;
	}
	cout << a[msg_size];
}