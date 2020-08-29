//author Margarita Shimanskaia
//implements standart segment tree
#include <iostream>
#include <stdio.h>
#include <sstream>
using namespace std;
 
#define MAX_A 524288
#define MAX_TREE_DEPTH 19
int cc = 0, depth;
 
typedef long long NUMBER;
 
static NUMBER a[MAX_A], tree_array[MAX_A] = {0};
static NUMBER *tree[MAX_TREE_DEPTH];
 
NUMBER sum(int a, int b) {
	int ct = cc , i = 1, aPos = 0, bPos = 0;
	NUMBER nsum = 0;
	for( ; i <= depth ; i++, ct >>= 1) 
		if((a & ct) || (b & ct)) {
			aPos = bPos = 1;
			nsum += tree[i][bPos];
			if(!(a & ct)) {
				nsum += tree[i][--aPos];
			}
			break;
		}
	for(i++ ; i <= depth ; i++) {
		aPos *= 2;
		bPos *= 2;
		ct >>= 1;
		if(a & ct) {
			nsum -= tree[i][aPos];
			aPos++;
		}
		if(!(b & ct)) {
			nsum -= tree[i][bPos + 1];
		}
		else
			bPos++;
	}
	
	return nsum;
}
 
int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for(int i = 0; i < n ; i++)
		cin >> a[i];
	cc = 1;
	int pt = 0;
	for(depth = 0; depth < MAX_TREE_DEPTH && cc < n ; depth++) { //distribute array into tree levels 
		tree[depth] = tree_array + pt;
		pt += cc;
		cc <<= 1;
	}
	cc >>= 1;
	tree[depth] = a;
	int nl = (n + 1) >> 1;
 
	for(int j = depth ; j > 0 ; j--, nl = (nl + 1) / 2) {
		NUMBER *high = tree[j - 1], *low = tree[j];
		for(int k = 0; k < nl ; k++)
			high[k] = low[k * 2] + low[k * 2 + 1];
	}
	string s;
	getline(cin, s);
	for (;;) {
		if(cin.eof())
			break;
		getline(cin, s);
		if (s.length() < 3)
			break;
		if (s[1] == 'e') {
			int x;
			NUMBER z;
			sscanf(s.c_str() + 4, "%d %lld", &x, &z);
			x--;
			NUMBER dif = z - a[x];
			a[x] = z;
			for (int j = depth - 1; j >= 0; j--)
			{
				x = x / 2;
				tree[j][x] += dif;
			}
		}
		if (s[1] == 'u') {
			int x, y;
			sscanf(s.c_str() + 4, "%d %d", &x, &y);
			if(x == y)
				cout << a[x - 1] << "\n";
			else
				cout << sum(x - 1, y - 1) << "\n";
		}
	}
	return 0;
}