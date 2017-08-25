import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
	public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = "";
        while((line = br.readLine()) != null){
            String[] s = line.trim().split(" ");
            int m = Integer.parseInt(s[0]);
            int n = Integer.parseInt(s[1]);
            List<Integer> list = new ArrayList<Integer>();
            for(int i=m;i<=n;i++){
                if(isF(i)){
                    list.add(i);
                }
            }
            if(list.size()==0){
                System.out.println("no");
            }else{
                for(int i=0;i<list.size();i++){
                    if(i!=list.size()-1){
                        System.out.print(list.get(i));
                        System.out.print(" ");
                    }else{
                        System.out.println(list.get(i));
                    }
                }
            }
        }
    }
    private static boolean isF(int x){
        int sum = 0;
        int a = x;
        while(a>0){
            int t = a % 10;
            sum += Math.pow(t, 3);
            a /= 10;
        }
        return sum == x;
    }
}