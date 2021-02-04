//builds a Hamiltonian cycle in a complete graph
import java.util.*;
 
public class olymp {
 
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[][] a = new int[n][n];
        int[] q = new int[n * (n + 1)];
        int start = 0;
        int end = n;
        for (int i = 1; i < n; i++) {
            q[i] = i;
            String s = in.next();
            for (int j = 0; j < i; j++) {
                a[i][j] = s.charAt(j) - '0';
                a[j][i] = a[i][j];
            }
        }
        for (int i = 0; i < n * (n - 1); i++) {
            if (a[q[start]][q[start + 1]] == 1) {
                q[end++] = q[start++];
            } else {
                for (int j = start + 2; j < end; j++) {
                    if((a[q[start]][q[j]] == 1) && (a[q[j + 1]][q[start + 1]] == 1)) {
                        int c = 0;
                        while (start + c + 1 < j - c) {
                            int temp = q[start + c + 1];
                            q[start + c + 1] = q[j - c];
                            q[j - c] = temp;
                            c++;
                        }
                        q[end++] = q[start++];
                        break;
                    }
                }
            }
        }
        for (int i = start; i < end; i++) {
            System.out.print(q[i] + 1 + " ");
        }
    }
 
}