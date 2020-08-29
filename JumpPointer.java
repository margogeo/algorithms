//author Margarita Shimanskaia
//finds the ancestor for every element on 2^0...log(n) level
import java.util.*;
import java.io.*;
import java.lang.Math;
 
public class JumpPointer {
 
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		if(n != 1) {
		    int k = (int)(((double)Math.log(n - 1)) / ((double)Math.log(2)));
		    int[][] a = new int[n + 1][k + 1];
		    int[][] used = new int[n + 1][k + 1];
		    int[] num = new int[k + 1];
		    for(int i = 1; i <= n; i++) {
			    a[i][0] = in.nextInt();
			    if(a[i][0] != 0) {
			    	used[++num[0]][0] = i;
			    }  	
		    }
		    for(int c = 1; c <= k; c++) {
		    	for(int i = 1; i <= num[c - 1]; i++) {
		    	    a[used[i][c - 1]][c] = a[a[used[i][c - 1]][c - 1]][c - 1];
		    	    if(a[used[i][c - 1]][c] != 0) {
				    	used[++num[c]][c] = used[i][c - 1];
				    }
		    	}
		    }
		    for(int i = 1; i <= n; i++) {
		    	StringBuilder sout = new StringBuilder(i + ":");
		    	int c = 0;
		    	while(c <= k && a[i][c] != 0) {
		    		sout.append(" " + a[i][c]);
		    		c++;
		    	}
		    	System.out.println(sout);
		    }
		} else {
			int x = in.nextInt();
			System.out.print(1 + ":");
		}
	}
}