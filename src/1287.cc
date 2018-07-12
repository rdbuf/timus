#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

struct Cell { uint32_t hor, ver, posdiag, negdiag, result; };

#define LOG(x) "  " #x " = " << (x)
ostream& operator<<(ostream& os, const array<Cell, 2>& cell) {
	return os << "S:" << LOG(cell[0].hor) << LOG(cell[0].ver) << LOG(cell[0].posdiag) << LOG(cell[0].negdiag) << LOG(cell[0].result) << "\n"
		<< "s:" << LOG(cell[1].hor) << LOG(cell[1].ver) << LOG(cell[1].posdiag) << LOG(cell[1].negdiag) << LOG(cell[1].result);
}

int main() {
	int n; cin >> n;
	vector<vector<char>> a(n, vector<char>(n));
	for (auto& x : a) for (auto& y : x) { char tmp; cin >> tmp; y = tmp == 's'; }

	vector<array<Cell, 2>> pprev_diag, prev_diag, this_diag;
	for (int diag_number = 1; diag_number <= n * 2 - 1; ++diag_number) {
		int s = (diag_number <= n ? diag_number : n * 2 - diag_number);
		this_diag.resize(s);
		for (int i = s - 1, a_i = max(0, diag_number - n); i != -1 && a_i < n; --i, ++a_i) {
			const int idx = a[a_i][diag_number-a_i-1];
			{
				int idx2 = i + 1;
				bool index_valid = idx2 < this_diag.size();
				this_diag[i][idx].posdiag = (index_valid ? this_diag[idx2][idx].posdiag : 0) + 1;
				if (index_valid) {
					this_diag[i][0].result = max(this_diag[i][0].result, this_diag[idx2][0].result);
					this_diag[i][1].result = max(this_diag[i][1].result, this_diag[idx2][1].result);
				}
			}
			{
				int idx2 = i + (this_diag.size() < prev_diag.size());
				bool index_valid = idx2 > -1 && idx2 < prev_diag.size();
				this_diag[i][idx].ver = (index_valid ? prev_diag[idx2][idx].ver : 0) + 1;
				if (index_valid) {
					this_diag[i][0].result = max(this_diag[i][0].result, prev_diag[idx2][0].result);
					this_diag[i][1].result = max(this_diag[i][1].result, prev_diag[idx2][1].result);
				}
			}
			{
				int idx2 = i - (this_diag.size() > prev_diag.size());
				bool index_valid = idx2 > -1 && idx2 < prev_diag.size();
				this_diag[i][idx].hor = (index_valid ? prev_diag[idx2][idx].hor : 0) + 1;
				if (index_valid) {
					this_diag[i][0].result = max(this_diag[i][0].result, prev_diag[idx2][0].result);
					this_diag[i][1].result = max(this_diag[i][1].result, prev_diag[idx2][1].result);
				}
			}
			{
				int idx2 = i - (this_diag.size() > prev_diag.size()) + (prev_diag.size() < pprev_diag.size());
				bool index_valid = idx2 > -1 && idx2 < pprev_diag.size();
				this_diag[i][idx].negdiag = (index_valid ? pprev_diag[idx2][idx].negdiag : 0) + 1;
				if (index_valid) {
					this_diag[i][0].result = max(this_diag[i][0].result, pprev_diag[idx2][0].result);
					this_diag[i][1].result = max(this_diag[i][1].result, pprev_diag[idx2][1].result);
				}
			}
			this_diag[i][idx].result = max({
				this_diag[i][idx].result,
				this_diag[i][idx].posdiag,
				this_diag[i][idx].ver,
				this_diag[i][idx].hor,
				this_diag[i][idx].negdiag
			});
		}
		pprev_diag = exchange(prev_diag, move(this_diag)), this_diag.clear();
	}

	auto S = prev_diag[0][0].result, s = prev_diag[0][1].result;
	if (s > S) cout << "s\n" << s;
	else if (s < S) cout << "S\n" << S;
	else cout << "?\n" << s;
}