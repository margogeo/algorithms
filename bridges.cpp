//finding every bridge in a graph
#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <cmath> 
#include <utility>
#include <cstdlib>
#include <numeric>
 
#define f first
#define s second
using namespace std;
#define min(a,b) (((a) < (b)) ? (a) : (b))
 
int n, m, k = 0;
bool  ans[2000001] = { 0 };
vector<vector<int> > g;
bool used[20001] = { 0 };
int t, tin[20001], fup[20001];
 
void dfs(int v, int predok) {//dfs от предка и текущей вершины
	used[v] = 1;
	tin[v] = fup[v] = t++;   // время входа и F up
	for (int i = 0; i < g[v].size(); i+=2) {
		int to = g[v][i]; // куда идем
		int num = g[v][i + 1];
		if (to == predok)  continue;     //в предка не идем(не надо)
		if (used[to])                    // если уже посетили, то обновим для нее F up
			fup[v] = min(fup[v], tin[to]);
		else {                           // если не посетили, то идем в нее
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]); // когда возваращаемся обновляем F up
			if (fup[to] > tin[v]) {         // если F up > время входа - то мы вышли из моста
				k++;
				ans[num] = 1;
			}
		}
	}
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	g.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
		g[a - 1].push_back(i);
		g[b - 1].push_back(a - 1);
		g[b - 1].push_back(i);
	}
 
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs(i, -1);
 
	cout << k << endl;
	for (int i = 0; i < m; i++) {
		if (ans[i] != 0) {
			cout << i + 1 << " ";
		}
	}
	return 0;
}