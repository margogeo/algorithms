//author Margarita Shimanskaia
//finds the lowest common ancestor for two elements
import java.util.*;
import java.io.*;
import java.lang.Math;
 
public class Lca {
 
	static int[] d;
	static int[][] a;
	public static void dep(int j) {
		if(a[j][0] == 1 || d[a[j][0]] != 0) {
			d[j] = d[a[j][0]] + 1;
			return;
		} else {
			dep(a[j][0]);
			d[j] = d[a[j][0]] + 1;
			return;
		}
	}
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		if(n != 1) {
		    int k = (int)(((double)Math.log(n-1)) / ((double)Math.log(2)));
		    a = new int[n + 1][k + 1];
		    d = new int[n + 1];
		    int[][] used = new int[n + 1][k + 1];
		    int[] num = new int[k + 1];
		    a[1][0] = 0;
		    for(int i = 2; i <= n; i++) {
			    a[i][0] = in.nextInt();
			    used[++num[0]][0] = i; 	
		    }
		    int[] pw = new int[k + 1];
		    pw[0] = 1;
		    for(int i = 1; i <= k; i++) {
		    	pw[i] = pw[i - 1] * 2;
		    }
		    for(int i = 2; i <= n; i++) {
		    	if(d[i] == 0)
		    		dep(i);
		    }
		    int m = in.nextInt();
		    for(int c = 1; c <= k; c++) {
		    	for(int i = 1; i <= num[c - 1]; i++) {
		    	    a[used[i][c - 1]][c] = a[a[used[i][c - 1]][c - 1]][c - 1];
		    	    if(a[used[i][c - 1]][c] != 0) {
				    	used[++num[c]][c] = used[i][c - 1];
				    }
		    	}
		    }
		    StringBuilder sout = new StringBuilder();
		    for(int i = 0; i < m; i++) {
		    	int u = in.nextInt();
		    	int v = in.nextInt();
		    	int diff;
		    	if(d[u] < d[v]) {
		    		int temp = u;
		    		u = v;
		    		v = temp;
		    	}
		    	diff = d[u] - d[v];
		    	if(diff > 0) {
		    	    int kk = (int)(((double)Math.log(diff)) / ((double)Math.log(2)));
		    	    for(int j = kk; j >= 0; j--) {
		    		    if(diff >= pw[j]) {
		    			    diff -= pw[j];
		    			    u = a[u][j];
		    		    }
		    		    if(diff == 0) {
		    			    break;
		    		    }
		    	    }
		    	}
		    	if(u != v) {
		    	    int kk = (int)(((double)Math.log(d[u])) / ((double)Math.log(2)));
		    	    for(int j = kk; j >= 0; j--) {
		    		    if(a[u][j] != a[v][j]) {
		    			    u = a[u][j];
		    			    v = a[v][j];
		    		    }
		    	    }
		    	    sout.append(a[u][0] + "\n");
		    	} else {
		    		sout.append(u + "\n");
		    	}
		    }
		    System.out.println(sout);
		} else {
			int x = in.nextInt();
			int m = in.nextInt();
		}
	}
}