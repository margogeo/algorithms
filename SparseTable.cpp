#include <iostream>
#include <algorithm>
#include <math.h> 
using namespace std;
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, a1, u, v;
	int r, u1, v1;
	cin >> n >> m >> a1;
	cin >> u >> v;
	int c = log(n) / log(2) + 1;
	int *b = new int[c + 1];
	b[0] = 1;
	unsigned int **mi = new unsigned int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		mi[i] = new unsigned int[c + 1];
	mi[1][0] = a1;
    for (int i = 2; i < n + 1; i++) {
		mi[i][0] = (23L * mi[i - 1][0] + 21563L) % 16714589;
    }
	for (int i = 1; i < c; i++) {
		b[i] = b[i - 1] * 2;
	}
	for (int i = 1; i < c; i++) {
		for (int j = 1; j <= n - b[i] + 1; j++) {
			mi[j][i] = min(mi[j][i - 1], mi[j + b[i - 1]][i - 1]);
		}
	}
	for (int i = 1; i <= m; i++) {
		if (u > v) {
			u1 = v;
			v1 = u;
		}
		else {
			u1 = u;
			v1 = v;
		}
		int k = log(v1 - u1) / log(2);
		int l = 1 << k;
		r = min(mi[u1][k], mi[v1 - l + 1][k]);
		if (i != m) {
			u = ((17 * u + 751 + r + 2 * i) % n) + 1;
			v = ((13 * v + 593 + r + 5 * i) % n) + 1;
		}
	}
    cout << u << " " << v << " " << r;
    return 0;
}