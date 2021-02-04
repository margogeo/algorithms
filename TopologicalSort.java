//returns topologically sorted vertices of an oriented graph
import java.util.*;
import java.math.BigInteger; 
import java.io.*;
 
public class algosy {
	
	static Stack<Integer>[] e;
	static Stack<Integer>[] tree;
    static int[] color;
    static int[] answer;
    static int ind;
	static int cycle(int u) {
		color[u] = 1;
		while(!e[u].isEmpty()) {
			int v = e[u].pop();
			if(color[v]  == 1)
				return -1;
			if(color[v] == 0)
				if( -1 == cycle(v))
					return -1;
		}
		color[u] = 2;
		return 0;
	}
	static void dfs(int u) {
		color[u] = 1;
		while(!tree[u].isEmpty()) {
			int v = tree[u].pop();
			if(color[v] == 0)
			    dfs(v);
		}
		answer[ind--] = u + 1;
	}
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
	    int n = in.nextInt();
	    int m = in.nextInt();
	    e = new Stack[n];
	    tree = new Stack[n];
	    color = new int[n];
	    answer = new int[n];
	    int check = 1;
	    for(int i = 0; i < n; i++) {
	    	e[i] = new Stack();
	    	tree[i] = new Stack();
	    }
	    for (int i = 0; i < m; i++) {
	    	int u = in.nextInt() - 1;
	    	int v = in.nextInt() - 1;
	    	e[u].push(v);
	    	tree[u].push(v);
	    } 
	    for (int i = 0; i < n; i++) {
	    	if (color[i] == 0) {
	    	    check = cycle(i);
	    	    if (check == -1)
	    		    break;
	    	}
	    }
	    if(check == -1)
	    	System.out.println(-1);
	    else {
	    	ind = n - 1;
	    	for (int i = 0; i < n; i++) {
	    		color[i] = 0;
	    	}
	    	for (int i = 0; i < n; i++) {
	    		if(color[i] == 0) {
	    			dfs(i);
	    		}
	    	}
	    	for(int i = 0; i < n; i++) {
	    		System.out.print(answer[i] + " ");
	    	}
	    }
    }
}