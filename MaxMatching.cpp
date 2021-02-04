//finds matching with maximum weight
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <future>
#include <algorithm>
 
using namespace std;
 
struct pr { int weight, ind; };
 
bool cmp(pr  a, pr b) {
    return a.weight < b.weight;
}
#define MAXN 1001
 
vector<int> g[MAXN];
 
vector<bool> check;
vector<int> m;
 
bool recs(int v) 
{
    if (!check[v]) {
        check[v] = true;
        for (int i : g[v]) {
            if (m[i] == -1 || recs(m[i])) {
                m[i] = v;
                return true;
            }
        }
    }
    return false;
};
 
 
int main() {
 
    ifstream fin("matching.in");
    ofstream fout("matching.out");
 
    int n = 0;
    fin >> n;
    vector<pr> w;
    vector<int> ans(n);
    m.reserve(n);
    check.reserve(n);
    int v = 0;
    for (int i = 0; i < n; i++) {
        fin >> v;
        w.push_back({ v, i });
    }
    sort(w.begin(), w.end(), cmp);
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        fin >> a;
        for (int j = 0; j < a; j++) {
            fin >> b;
            g[i].push_back(b - 1);
        }
    }
    m.assign(n, -1);
 
    for (auto i = w.crbegin(); i != w.crend(); i++) {
        check.assign(n, false);
        recs(i->ind);
    }
    ans.assign(n, -1);
     
    for (int i = 0; i < n; i++) 
        if (m[i] != -1)
            ans[m[i]] = i;
     
    for (int i = 0; i < n; i++) {
        fout << (ans[i] + 1) << " ";
    }
    return 0;
}