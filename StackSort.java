import java.util.*;
import java.io.*;
import java.lang.Math;
import java.math.BigInteger;
 
public class StackSort {  
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] a = new int[n + 2];
		int[] b = new int[n + 2];
		int[] c = new int[2 * n];
		//1 - push, 2 - pop
		int aj = 0, l = 1, cj = 0, imp = 0;
		for(int i = 0; i <= n; i++) {
			b[i] = -1;
		}
		int nx = 1;
		for(; nx <= n ; ) {
			if(aj > 0 && a[aj - 1] == nx) {
			   c[cj++] = 2;
			   aj--;
			   nx++;
			   continue;
			}
			if(b[nx] >= 0) {
				imp = 1;
				break;
			}
		    int nd = in.nextInt();
		    b[nd] = aj;
		    a[aj++] = nd;
		    c[cj++] = 1;
	    }
		if(imp == 1)
			System.out.println("impossible");
		else
			for(int i = 0; i < cj ; i++)
				if(c[i] == 1)
					System.out.println("push");
				else
					System.out.println("pop");
	}
}