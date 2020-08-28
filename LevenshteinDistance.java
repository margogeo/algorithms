import java.util.*;
import java.io.*;
 
public class LevenshteinDistance {  
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
        String s = in.next();
        String l = in.next();
        char[] ss = s.toCharArray(); 
        char[] ll = l.toCharArray();
        int a = s.length();
        int b = l.length();
        int[][] d = new int[a + 1][b + 1];
        for(int i = 0; i < a; i++) {
        	d[i][0] = i;
        }
        for(int i = 0; i < b; i++) {
        	d[0][i] = i;
        }
        for(int i = 1; i <= a; i++) {
        	for(int j = 1; j <= b; j++) {
        		int c = Math.min(Math.min(d[i - 1][j - 1], d[i][j - 1]), d[i - 1][j]) + 1;
        		if(ss[i - 1] == ll[j - 1]) {
        			d[i][j] = d[i - 1][j - 1];
        		} else {
        			d[i][j] = c;
        		}
        	}
        }
        System.out.println(d[a][b]);
	}
}