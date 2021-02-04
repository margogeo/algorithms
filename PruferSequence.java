//builds Prufer sequence for a tree
import java.util.*;
import java.math.BigInteger; 
import java.io.*;
  
public class algosy {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        Set<Integer>[] edge = new Set[n];
        int[] a = new int[n];
        StringBuilder ans = new StringBuilder(); 
        int s = n;
        int[] check = new int[n];
        TreeSet<Integer> min = new TreeSet<Integer>();
        for (int i = 0; i < n; i++) {
            edge[i] = new HashSet();
        }
        for (int i = 1; i < n; i++) {
            int u = in.nextInt() - 1;
            int v = in.nextInt() - 1;
            edge[u].add(v);
            edge[v].add(u);
            a[u]++;
            a[v]++;
        } 
        for (int i = 0; i < n; i++) {
            if (a[i] == 1)
                min.add(i);
        }
        while (s > 2) {
            int i = min.pollFirst();
            int c = -1;
            for (int d : edge[i]) {
                c = d;
            }
            a[c]--;
            ans.append(c + 1 + " ");
            edge[c].remove(i);
            edge[i].remove(c);
            if(a[c] == 1)
                min.add(c);
            a[i]--;
            s--; 
        }
        System.out.println(ans.toString());
    }
}