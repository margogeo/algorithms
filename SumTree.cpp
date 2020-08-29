//author Margarita Shimanskaia
//builds a balanced binary tree and implements 
//                                  1. add(i) - adding an element with key i; 
//                                  2. sum(l, r) - returns sum of tree elements from [l; r]
#include <string>
#include <iostream>
 
using namespace std;
 
#define MAX_ELEM 400010
 
struct elem {
	int key;
	int count;
	long long sum;
	elem* left;
	elem* right;
	elem* par;
};
 
static elem* head = NULL;
elem elems[MAX_ELEM];
int a, b, elnext = 1;
 
elem* new_elem(int newKey) {
	elem* el = elems + elnext++;
	el->key = newKey;
	el->count = 0;
	el->par = NULL;
	el->left = NULL;
	el->right = NULL;
	el->sum = newKey;
	return el;
}

int mov = 0;
 
void moveUp(elem* r) {
	mov++;
	elem* par = r->par;
	if (par == NULL)
		return;
	elem* rot = par->par;
	if (rot)
		if (rot->left == par)
			rot->left = r;
		else
			rot->right = r;
	else
		head = r;
	r->par = rot;
	par->par = r;
	long long sum = par->sum;
 
	if (par->left == r) {
		long long dsum = r->key;
		if (r->left) {
			dsum += r->left->sum;
		}
		par->left = r->right;
		if (r->right)
			r->right->par = par;
		r->right = par;
		par->sum -= dsum;
	}
	else {
		long long dsum = r->key;
		if (r->right) {
			dsum += r->right->sum;
		}
		par->right = r->left;
		if (r->left)
			r->left->par = par;
		r->left = par;
		par->sum -= dsum;
	}
	r->sum = sum;
}
 
 
elem* search() {
	elem* r = head, * ne;
	for (;;) {
		if (r->key == a)
			return r;
 
		if (r->left && r->left->count > 7 && (r->right == NULL || r->left->count > r->right->count + 7)) {
			r->left->count -= 5;
			moveUp(ne = r->left);
			r = ne;
		}
		else
			if (r->right && r->right->count > 7 && (r->left == NULL || r->right->count > r->left->count + 7)) {
				r->right->count -= 5;
				moveUp(ne = r->right);
				r = ne;
			}
		if (r->key == a) {
			return r;
		}
		r->count++;
 
		if (a < r->key) {
			if (r->left == NULL) {
				return r;
			}
			else
				r = r->left;
		}
		else {
			if (r->right == NULL) {
				return r;
			}
			else
				r = r->right;
		}
	}
}
 
elem* search2() {
	elem* r = head;
	if (r != NULL) {
		for (;;) {
			if (r->key == a)
				return r;
			if (a < r->key) {
				if (r->left == NULL) {
					return NULL;
				}
				else
					r = r->left;
			}
			else {
				if (r->right == NULL) {
					return NULL;
				}
				else
					r = r->right;
			}
		}
	}
	else { 
	    return NULL; 
	}
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n = 0, nCmd;
	long long sum = 0;
	head = NULL;
	cin >> nCmd;
	char cmd[10], prevCmd = 0;
	for (int i = 0; i < nCmd; i++) {
		cin >> cmd >> a;
		if (*cmd == '+') {
			if (prevCmd == '?')
				a = (a + sum) % 1000000000;
			else 
				a %= 1000000000;
			if (search2() == NULL) 
			{
				if (n == 0) {
					head = new_elem(a);
					n++;
				}
				else {
					elem* t = search();
					if (t->key == a) {
						continue;
					}
					elem* k = new_elem(a);
					n++;
					if (a < t->key) {
						t->left = k;
					}
					else {
						t->right = k;
					}
					k->par = t;
					for (k = t; k != NULL; k = k->par) {
						k->sum += a;
					}
				}
			}
		}
		if (*cmd == '?') {
			cin >> b;
			sum = 0LL;
			if (n != 0 && b >= a) {
				elem* r = head;
				sum = head->sum;
				for (;;) {
					if (a >= r->key && r->left)
						sum -= r->left->sum;
					if (a < r->key && r->left == NULL || a == r->key)
						break;
					if (a < r->key)
						r = r->left;
					else {
						sum -= r->key;
						if (r->right)
							r = r->right;
						else
							break;
					}
				}
				for (r = head;;) {
					if (b <= r->key && r->right)
						sum -= r->right->sum;
					if (b > r->key&& r->right == NULL || b == r->key)
						break;
					if (b > r->key)
						r = r->right;
					else {
						sum -= r->key;
						if (r->left)
							r = r->left;
						else
							break;
					}
				}
			}
			cout << sum << endl;
		}
		prevCmd = *cmd;
	}
	return 0;
}