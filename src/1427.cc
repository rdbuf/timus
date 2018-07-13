#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

// plain greedy approach
int main() {
	int n, m; cin >> n >> m;
	string msg; getline(cin, msg), getline(cin, msg);
	int msgs = 0;
	for (
		size_t i = 0;
		i < msg.length();
		i += max<int>(find_if_not(
				min(msg.end(), msg.begin() + i),
				min(msg.end(), msg.begin() + i + m),
				[](const char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' '; }
			) - min(msg.end(), msg.begin() + i), n)
	) msgs += 1;
	cout << msgs;
}