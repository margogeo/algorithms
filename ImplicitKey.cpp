//author Margarita Shimanskaia
//builds a binary tree with implicit key 
//implements adding(i, x) and deleting(i) items after element number i in the tree
#include <string>
#include <iostream>
 
using namespace std;
 
#define MAX_ELEM 200010
 
struct elem {
	int key;
	int num;
	elem* left;
	elem* right;
	elem* par;
};
 
static elem* head = NULL;
elem elems[MAX_ELEM];
int a, elnext = 1;
 
elem* new_elem(int newKey) {
	elem* el = elems + elnext++;
	el->key = newKey;
	el->par = NULL;
	el->left = NULL;
	el->right = NULL;
	el->num = 1;
	return el;
}
 
void del(elem* r) {
	elem* nr = NULL;
	if (r->left != NULL && r->right == NULL)
		nr = r->left;
	else if (r->right != NULL) {
		nr = r->right;
		if (r->left != NULL) {
			elem* nl = r->right;
			int num = r->left->num;
			nl->num += num;
			while (nl->left != NULL) {
				nl = nl->left;
				nl->num += num;
			}
			nl->left = r->left;
			r->left->par = nl;
		}
	}
	if (r->par != NULL) {
		if (r->par->left == r)
			r->par->left = nr;
		if (r->par->right == r)
			r->par->right = nr;
		if (nr != NULL)
			nr->par = r->par;
	}
	else {
		head = nr;
		if (nr != NULL)
			nr->par = NULL;
	}
}
 
void moveUp(elem* r) {
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
	int num = par->num;
	if (par->left == r) {
		int sub = 1;
		if (r->left)
			sub += r->left->num;
		par->left = r->right;
		if (r->right)
			r->right->par = par;
		r->right = par;
		par->num -= sub;
	}
	else {
		int sub = 1;
		if (r->right)
			sub += r->right->num;
		par->right = r->left;
		if (r->left)
			r->left->par = par;
		r->left = par;
		par->num -= sub;
	}
	r->num = num;
}
 
elem* findMax(int k, int dif)
{
	elem* r = head, *ne;
	int sum = 0;
	for (;;) {
		static int cnt = 0;
		if (dif > 0 && (++cnt & 15) == 1) {
			if (r->left && r->left->num > 7 && (r->right == NULL || r->left->num > r->right->num + 7)) {
				moveUp(ne = r->left);
				r = ne;
			}
			else
				if (r->right && r->right->num > 7 && (r->left == NULL || r->right->num > r->left->num + 7)) {
					moveUp(ne = r->right);
					r = ne;
				}
		}
		r->num += dif;
		int t = sum;
		if (r->left)
			t += r->left->num;
		if (t + 1 == k)
			return r;
		if (t >= k)
			r = r->left;
		else {
			sum = t + 1;
			r = r->right;
		}
	}
}
 
void tout(elem* x) {
	if (x != NULL) {
		tout(x->left);
		cout << x->key << endl;
		tout(x->right);
	}
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n = 0, cmd, m;
	head = NULL;
	cin >> n >> m;
	elem* prev = NULL;
	for (int i = 0; i < n; i++) {
		cin >> a;
		elem* t = new_elem(a);
		if (prev == NULL) {
			head = t;
		}
		else {
			elem* r = findMax(i, 1);
			if (r->right == NULL) {
				r->right = t;
				t->par = r;
			}
			else {
				t->right = r->right;
				t->num = t->right->num + 1;
				r->right->par = t;
				r->right = t;
				t->par = r;
			}
		}
		prev = t;
	}
 
	for (int i = 0; i < m; i++) {
		char cmd[20];
		int c = 0, d = 0;
		cin >> cmd >> c;
		if (cmd[0] == 'a') {
			cin >> d;
			elem* j = new_elem(d);
			n++;
			if (n == 1) {
				head = j;
			} else if (c == 0) {
				elem* r = findMax(1,1);
				r->left = j;
				j->par = r;
			} else {
				elem* r = findMax(c,1);
				if (r->right == NULL) {
					r->right = j;
					j->par = r;
				}
				else {
					j->right = r->right;
					j->num = j->right->num + 1;
					r->right->par = j;
					r->right = j;
					j->par = r;
				}
			}
		}
		else {
			n--;
			elem* r = findMax(c, -1);
			if (r)
				del(r);
			else
				n += 0;
		}
	}
	cout << n << endl;
    tout(head);
	return 0;
}