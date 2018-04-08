#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    const int side = 100;
    int n, m; cin >> n >> m; n += 1, m += 1;
    vector<vector<double>> d(n);
    for (auto& a : d) a.resize(m);
    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int x, y; cin >> x >> y;
        d[x][y] = -2;
    }

    d[0][0] = 0;
    for (int i = 1; i < n; ++i) d[i][0] = d[i-1][0] + 100;
    for (int i = 1; i < m; ++i) d[0][i] = d[0][i-1] + 100;

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            d[i][j] = min({d[i-1][j] + 100, d[i][j-1] + 100, (d[i][j] == -2 ? d[i-1][j-1] + sqrt(2 * side * side) : numeric_limits<int>::max())});
        }
    }

    cout << round(d[n-1][m-1]);
}