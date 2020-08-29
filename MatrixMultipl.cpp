//author Margarita Shimanskaia
//effectively multiplies a lot of 2x2 matrices by request
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <memory.h>
using namespace std;
 
#define MAX_A 265000
#define MAX_TREE_DEPTH 20
#define TRN_SIZE 50
int depth, r;
 
ifstream fin("crypto.in");
ofstream fout("crypto.out");
 
struct matrix {
	int a, b, c, d;
};
 
matrix mr; 
 
void mult(matrix &x, matrix &y) {
	mr.a = (x.a * y.a + x.b * y.c) % r;
	mr.b = (x.a * y.b + x.b * y.d) % r;
	mr.c = (x.c * y.a + x.d * y.c) % r;
	mr.d = (x.c * y.b + x.d * y.d) % r;
}
 
void mout(matrix &x) {
	fout << x.a << " " << x.b << "\n";
	fout << x.c << " " << x.d << "\n\n";
}
 
static matrix a[MAX_A], tree_array[MAX_A];
static matrix* tree[MAX_TREE_DEPTH];
 
struct Node { 
    int lv, ind; 
};
static Node nod[TRN_SIZE];
static int il = 0, ir = 0;
 
//Get binary tree between two points
int getTree(int l, int r) {
	il = 0;
	ir = TRN_SIZE - 1;
	int k = depth;
	while (l <= r) {
		if (l & 1) {
			nod[il].lv = k;
			nod[il++].ind = l;
		}
		if (!(r & 1)) {
			nod[ir].lv = k;
			nod[ir--].ind = r;
		}
		if(l >= r)
			break;
		l = (l + 1) / 2, r = (r - 1) / 2;
		k--;
	}		
	int kr = TRN_SIZE - ir - 1;
	return il + kr;
}
 
void sum(int a, int b) {
	matrix nsum = {1, 0, 0, 1};
	getTree(a, b);
	for(int i = 0; i < il; i++) {
		mult(nsum,tree[nod[i].lv][nod[i].ind]);
		nsum = mr;
	}
	for(int i = ir+1; i < TRN_SIZE; i++) {
		mult(nsum,tree[nod[i].lv][nod[i].ind]);
		nsum = mr;
	}
	mout(nsum);
}
 
int main(void) {
	fin.tie(0);
	fout.tie(0);
	int n, m;
	memset(tree_array, 0, sizeof(tree_array));
	fin >> r >> n >> m;
	for (int i = 0; i < n; i++) {
		fin >> a[i].a;
		fin >> a[i].b;
		fin >> a[i].c;
		fin >> a[i].d;
		a[i].a = a[i].a % r;
		a[i].b = a[i].b % r;
		a[i].c = a[i].c % r;
		a[i].d = a[i].d % r;
	}
	memset(a + n, 0, sizeof(matrix) * 15);
	int cc = 1;
	int pt = 0;
	for(depth = 0; depth < MAX_TREE_DEPTH && cc < n; depth++) { //distribute array into tree levels
		tree[depth] = tree_array + pt;
		pt += cc;
		cc <<= 1;
	}
	tree[depth] = a;
	int nl = (n + 1) >> 1;
 
	for (int j = depth; j > 0; j--, nl = (nl + 1) / 2) {
		matrix* high = tree[j - 1], * low = tree[j];
		for (int k = 0; k < nl; k++) {
			mult(low[k * 2], low[k * 2 + 1]);
			high[k] = mr;
		}
		if(nl == 1)
			break;
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		fin >> x >> y;
		if(x > y) {
			int z = x;
			x = y;
			y = z;
		}
		if (x == y)
			mout(a[x - 1]);
		else {
			sum(x - 1, y - 1);
		}
	}
	return 0;
}