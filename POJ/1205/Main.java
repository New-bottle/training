import java.math.*;
import java.util.*;

public class Main{
	static int N = 110;
	static int n;
	static BigInteger Zero = new BigInteger("0");
	static BigInteger One = new BigInteger("1");
	static BigInteger t = new BigInteger("0");
	static BigInteger[] f = new BigInteger[N];
	public static void main(String[] args){
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			n = cin.nextInt();
			f[0] = One;
			for(int i = 1; i <= n; i ++){
				f[i] = Zero;
				for(int j = 1; j <= i; j ++){
					t = BigInteger.valueOf(i - j + 1);
					f[i] = f[i].add(f[j - 1].multiply(t));
				}
			}
			System.out.println(f[n]);
		}
	}
}
