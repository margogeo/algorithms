import java.lang.*;
import java.util.*;
import java.io.*;
 
public class GoblinShaman {
    public static void main(String[] args) throws IOException {
	    Deque<Integer>qA = new ArrayDeque<Integer>();
	    Deque<Integer> qB = new ArrayDeque<Integer>();
	    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	    BufferedWriter wout = new BufferedWriter(new OutputStreamWriter(System.out));
 
	    String s = in.readLine();
	    int n = Integer.parseInt(s);
	    for (int i = 0; i < n ; i++) {
		    s = in.readLine();
		    char c = s.charAt(0);
		    if (c == '-') {
			    s = qA.pollFirst() + "\n";
			    wout.write(s);
		    }
		    else {
			    Integer k = Integer.parseInt(s.substring(2));
			    if (c == '+') {
				    qB.addLast(k);
			    }
			    if (c == '*') {
				    if (qA.size() >= qB.size() + 1) 
					    qB.addFirst(k);
				    else 
					    qA.addLast(k);
			    }
		    }
		    if (qB.size() > qA.size()) 
			    qA.addLast(qB.pollFirst());
	    }
	    wout.close();
    }
}  