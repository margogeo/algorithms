//author Margarita Shimanskaia
//delets the least number of brackets and returns a balanced bracket sequence
import java.util.*;
import java.io.*;
import java.math.*;
 
 
public class BracketSequence {  
	static String s, ous = new String();
 
	static void answer(int j, int i, int[][] m , int[][] sum)
	{
		if(m[j][i] == i - j + 1)
			return;
		if(m[j][i] == 0) {
			ous += s.substring(j,i + 1);
			return;
		}
		if(sum[j][i] == -1) {	
			ous += s.substring(j,j + 1);
			answer(j + 1, i - 1, m, sum);
			ous += s.substring(i,i + 1);
		}
		else {
			answer(j, sum[j][i], m, sum);	
			answer(sum[j][i] + 1, i, m, sum);
		}
	}
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		s = in.next();
		int n = s.length();	
		int[] a = new int[n];
		int max = Integer.MAX_VALUE;
		int[][] m = new int[n][n];
		int[][] sum = new int[n][n];
		int l = -1;
		String def = "({[)}]";
		for(int i = 0; i < n; i++) {
			a[i] = def.indexOf(s.charAt(i));
		}
		for(int i = 0; i < n; i++) {
			m[i][i] = 1;
			for(int j = i - 1; j >= 0; j--) {
				max = Integer.MAX_VALUE;
				l = -1;
		       if(a[j] == a[i] - 3) {
		    	  max = m[j + 1][i - 1]; 
		       } 
		       for(int h = j; h < i; h++) {
		    	   if(m[j][h] + m[h + 1][i] < max) {
		    		   l = h;
		    		   max = m[j][h] + m[h + 1][i];
		    	   }
		       }
		       m[j][i] = max;
		       sum[j][i] = l; 
			}
		}
		answer(0, n - 1, m, sum);
		System.out.println(ous);
	}
}