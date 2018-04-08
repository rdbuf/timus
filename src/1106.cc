#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

// Took a couple of hints from the forum. Yet has to be proven correct.

int main() {
    int n; cin >> n;
    vector<vector<int>> friendship(n);
    for (int i = 0; i < n; ++i) {
        int friend_;
        while (cin >> friend_, friend_) friendship[i].push_back(friend_-1);
    }

    vector<int> membership(n, -1);

    for (int i = 0; i < n; ++i) {
        bool has_indicent_0 = false;
        for (int j : friendship[i]) {
            has_indicent_0 |= (membership[j] == 0);
        }
        membership[i] = has_indicent_0;
    }

    cout << count(membership.begin(), membership.end(), 0) << "\n";
    for (int i = 0; i < n; ++i) {
        if (membership[i] == 0) cout << i + 1 << " ";
    }
}