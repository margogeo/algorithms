#include <string>
#include <iostream>
 
using namespace std;
 
#define MAX_ELEM 100010
 
struct elem {
	int key;
	int count;
	int num;
	elem *left;
	elem *right;
	elem *par;
};
 
static elem *head = NULL;
elem elems[MAX_ELEM];
int a, elnext = 1;
 
elem* new_elem(int newKey) {
	elem *el = elems + elnext++;
	el->key = newKey;
	el->count = 0;
	el->par = NULL;
	el->left = NULL;
	el->right = NULL;
	el->num = 1;
	return el;
}
 
void del(elem *r) {
	elem *nr = NULL;
	if (r->left != NULL && r->right == NULL)
		nr = r->left;
	else if (r->right != NULL) {
		nr = r->right;
		if (r->left != NULL) {
			elem *nl = r->right;
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
 
void moveUp(elem *r) {
	elem *par = r->par;
	if (par == NULL)
		return;
	elem *rot = par->par;
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
 
 
elem* search(int dif) {
	elem *r = head, *ne;
	for (;;) {
		if (r->key == a)
			return r;
		if (dif > 0) {
			if (r->left && r->left->count > 5 && (r->right == NULL || r->left->count > r->right->count + 5)) {
				moveUp(ne = r->left);
				r = ne;
			}
			else
				if (r->right && r->right->count > 5 && (r->left == NULL || r->right->count > r->left->count + 5)) {
					moveUp(ne = r->right);
					r = ne;
				}
			if (r->key == a)
				return r;
		}
		r->num += dif;
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
 
elem* findMax(int k)
{
	elem *r = head;
	int sum = 0;
	for (;;)
	{
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
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n = 0, nCmd, cmd;
	head = NULL;
	cin >> nCmd;
	for (int i=0; i < nCmd ;i++) {
		cin >> cmd >> a;
		if (cmd > 0) {
			if (n == 0) {
				head = new_elem(a);
				n++;
			}
			else {
				elem *t = search(1);
				if (t->key == a)
					continue;
				elem *k = new_elem(a);
				n++;
				if (a < t->key) {
					t->left = k;
				}
				else {
					t->right = k;
				}
				k->par = t;
			}
		}
		if (cmd < 0) {
			elem *r = search(-1);
			if (r != NULL) {
				n--;
				del(r);
			}
		}
		if (cmd == 0) {
			elem *r = findMax(n - a + 1);
			if (r != NULL)
				cout << r->key << endl;
		}
	}
	return 0;
}