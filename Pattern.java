//author Margarita Shimanskaia
import java.util.*;
import java.io.*;
 
public class Pattern {  
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int m = in.nextInt();
		if(n == 1 || m == 1) {
		  System.out.println(1 << (n * m));
		  return;
		}
		if(n > m) {
		  int nm = n;
		  n = m;
		  m = nm;
		}
		int c = 0; 
		int np = 1 << n;
		int sum = 0;
		int[][] a = new int[m][np];
		int[][] d = new int[np][np];
		for(int i = 0; i < np; i++) {
			for(int j = 0; j < np; j++) {
				int det = 1;
				for(int k = 0; k < n-1; k++) {
					int msk = 3 << k;
					int im = msk & i, jm = msk & j;
					if(im == 0 && jm == 0 || im == msk && jm == msk) {
						det = 0;
						break;
					}
						
				}
				d[i][j] = det;
			}
		}
		for(int i = 0; i < np; i++) 
		{
			a[0][i] = 1;
		}
		for(int t = 1; t < m; t++)
		{
			for(int i = 0; i < (1 << n); i++)
			{
				for(int j = 0; j < (1 << n); j++)
				{
					a[t][i] += a[t - 1][j] * d[j][i];
				}
			}	
		} 
		for(int i = 0; i < (1 << n); i++)
		{
			sum += a[m - 1][i]; 
		}
		System.out.println(sum);
	}
} 