//author Margarita Shimanskaia
//implements disjoint set with minimum and maximum key for each set
import java.util.*;
import java.io.*;
import java.lang.Math;
import java.math.BigInteger;
 
public class DisjointSet {  
	static int[] host;
	static int getHost(int i) {
	  int in = i;	
	  while (host[i] > 0) 
		  i = host[i];
	  if (i != in)
		  host[in] = i;
	  return i;
	}
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String s = in.readLine();
		int n = Integer.parseInt(s);
		n++;
		int[] max = new int[n];
		int[] min = new int[n];
		int[] num = new int[n];
		host = new int[n];
		for(int i = 1; i < n; i++) {
		 	min[i] = i;
			max[i] = i;
			num[i] = 1;
		}
		BufferedWriter wout = new BufferedWriter( new OutputStreamWriter(System.out));
		while(true){
			s = in.readLine();
			if( s == null)
				break;
			if(s.charAt(0) == 'u') {
				int e = 6;
				for( ; e < s.length(); e++)
					if(s.charAt(e)<=' ')
						break;
				int a = Integer.parseInt(s.substring(6,e));
				int b = Integer.parseInt(s.substring(e+1));
				a = getHost(a);
				b = getHost(b);
 
				if(a == b)
					continue;
				max[a] = Math.max(max[a], max[b]);
				min[a] = Math.min(min[a], min[b]);
				num[a] += num[b];
				host[b] = a;
			}
			if(s.charAt(0) == 'g') {
				int c = getHost(Integer.parseInt(s.substring(4)));
				s = new String(min[c] + " " + max[c] + " " + num[c] + "\n");
				wout.write(s);
			}
		}
		wout.close();
	}
}