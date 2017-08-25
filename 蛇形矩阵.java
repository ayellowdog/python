package onlineTest;

import java.util.Scanner;

public class f {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int top = 0;
		int down = n - 1;
		int left = 0;
		int right = n - 1;
		int mark = 1;
		int[][] resArr = new int[n][n];
		while(mark <= n*n){
			for (int i = top; i <= down; i++) {
				resArr[i][right] = mark;
				mark = mark + 1;
			}
			right = right - 1;
			for (int i = right; i >= left; i--) {
				resArr[down][i] = mark;
				mark = mark + 1;
			}
			down = down - 1;
			for (int i = down; i >= top; i--) {
				resArr[i][left] = mark;
				mark = mark + 1;
			}
			left = left + 1;
			for (int i = left; i <= right; i++) {
				resArr[top][i] = mark;
				mark = mark + 1;
			}
			top = top + 1;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				System.out.print(resArr[i][j] + " ");
			}
			System.out.println("");
		}
		

	}

}
