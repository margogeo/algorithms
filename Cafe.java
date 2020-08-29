//author Margarita Shimanskaia
//finds the best way to spend cafe tickets and use the discount 
//using dynamic programming
import java.util.*;
import java.io.*;
import java.math.*;
 
public class Cafe {
    public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] a = new int[n + 1]; 
		int[][] dp = new int[n + 1][n + 1];
		int[][] used = new int[n + 1][n + 1];
		for(int i = 1; i < n + 1; i++) {
			a[i] = in.nextInt();
		}
		if(n == 1) {
			System.out.println(a[1]);
			if(a[1] > 100)
			   System.out.println(1 + " " + 0);
			else
				System.out.println(0 + " " + 0);
		} else {
		    dp[0][0] = 0;
		    used[0][0] = 0;
		    for(int i = 1; i < n + 1; i++) {
			    dp[0][i] = 1000000;
			    dp[i][n] = 1000000;
			    used[0][i] = 0;
			    used[i][n] = 0;
		    }
            for(int i = 1; i < n + 1; i++) {
        	    for(int j = 0; j < n; j++) {
        		    if(a[i] <= 100) {
        			    if(dp[i - 1][j] + a[i] < dp[i - 1][j + 1]) {
        			        used[i][j] = used[i - 1][j];
        			    	dp[i][j] = dp[i - 1][j] + a[i];
        			    } else {
        			    	used[i][j] = used[i - 1][j + 1];
        			    	dp[i][j] = dp[i - 1][j + 1];
        			    }
        			         
        		    } else {
        			    if(j == 0) {
        				    if(dp[i - 1][j] + a[i] < dp[i - 1][j + 1]) {
        					    dp[i][j] = dp[i - 1][j] + a[i];
        					    used[i][j] = used[i - 1][j] + 1;
        				    } else {
        					    dp[i][j] = dp[i - 1][j + 1];
        					    used[i][j] = used[i - 1][j + 1];
        				    }
        			    } else {
        			        if(dp[i - 1][j - 1] + a[i] < dp[i - 1][j + 1]) {
        				        used[i][j] = used[i - 1][j - 1] + 1;
        				        dp[i][j] = dp[i - 1][j - 1] + a[i];
        			        } else {
        				        dp[i][j] = dp[i - 1][j + 1];
        				        used[i][j] = used[i - 1][j + 1];
        			        }
        			    }
        		    }
        	    }
            }
            int min = 1000000; 
            int index = 0;
            for(int i = 0; i < n + 1; i++) {
        	    if(dp[n][i] < min) {
        		    index = i;
        		    min = dp[n][i];
        	    }
        	    if(dp[n][i] == min) {
        		    index = i;
        	    }
            }
            System.out.println(min);
            System.out.println(index  + " " + (used[n][index] - index));
            int num = used[n][index] - index;
            int[] days = new int[num];
            int ind = num - 1;
            for(int i = n; i > 0; i--) {
        	    if(dp[i][index] == dp[i - 1][index + 1]) {
        		    days[ind] = i;
        		    ind--;
        		    index++;
        	    } else {
        		    if(index > 0 && a[i] > 100) {
        			    if(dp[i][index] == dp[i-1][index - 1] + a[i]) 
        				    index--;		
        		    }
        	    }
            }
            for(int i = 0; i < num; i++) {
        	    System.out.println(days[i]);
            }
		}
	}
}