import java.util.*;
import java.io.*;
 
public class BinTree {
	static elem head = null;
 
	static elem left(elem r) {
		if (r.left != null)
			return left(r.left);
		return r;
	}
 
    static void del(elem r) {
		elem nr = null;
		if (r.left != null && r.right == null)
			nr = r.left;
		else if (r.right != null) {
			nr = r.right;
			if (r.left != null) {
				elem nl = left(r.right);
				nl.left = r.left;
				r.left.par = nl;
			}
		}
		if (r.par != null) {
			if (r.par.left == r)
				r.par.left = nr;
			if (r.par.right == r)
				r.par.right = nr;
			if (nr != null)
				nr.par = r.par;
		}
		else {
			head = nr;
			if (nr != null)
				nr.par = null;
		}
    }
 
	static elem search(elem r, int a) {
		if (r == null) {
			return null;
		}
		if (r.key == a) {
			return r;
		}
		if ( a < r.key) {
			return search(r.left, a);
		}
		return search(r.right, a);
	}
 
	static elem next(elem r, elem best, int a) {
		if (r == null) {
			return best;
		}
		if (r.key > a && (best == null || best.key > r.key)) {
			best = r;
		}
		return next(r.right, next(r.left, best, a), a);
	}
 
	static elem prev(elem r, elem best, int a) {
		if (r == null) {
			return best;
		}
		if (r.key < a && (best == null || best.key < r.key)) {
			best = r;
		}
		return  prev(r.left, prev(r.right, best, a), a);
	}
 
	public static void main(String[] args) throws IOException {
    	Scanner in = new Scanner(System.in); 
    	int a;
    	int n = 0;
		head = null;
    	while(in.hasNext()) {
    		char s = (in.next()).charAt(0);
    		a = in.nextInt();
    		if (s == 'i') {
				if (search(head, a) != null)
					continue;
 
    			elem k = new elem(a);
				n++;
    			if(n == 1) {
    				head = k;
    			} else {
					elem t = null;
					if ((n & 1) != 0)
						t = next(head, null, a);
					if (t == null)
						t = prev(head, null, a);
					if (t == null)
						t = next(head, null, a);
					k.par = t;
					if (a < t.key) {
						k.left = t.left;
						t.left = k;
						if (k.left != null)
							k.left.par = k;
					}	
					else {
						k.right = t.right;
						t.right = k;
						if (k.right != null)
							k.right.par = k;
					}
				} 
			}
 
			if (s == 'd') {
    			elem r = search(head, a);
    			if(r != null) {
    				n--;
					del(r);
				}
    		} 
 
			if (s == 'e') {
    			elem r = search(head, a);
			    if (r != null) 
					System.out.println("true");
			    else
					System.out.println("false"); 
    		} 
 
			if (s == 'n') {
    			elem search = next(head, null, a);
				if (search == null) 
					System.out.println("none");
				else 
					System.out.println(search.key);
    		} 
			
			if (s == 'p') {
    			elem search = prev(head, null, a);
				if (search == null) 
					System.out.println("none");
				else 
					System.out.println(search.key);
    		}
    	}
    }
}
 
class elem {
	int key;
	elem left;
	elem right;
	elem par;
	elem(int newKey) {
	  key = newKey;
	  left = null;
	  right = null;
	  par = null;
	}
}