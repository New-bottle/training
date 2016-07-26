import java.math.*;
import java.util.*;

public class Main{
	static BigDecimal a, ans, base, tmp;
	static BigDecimal Eight = new BigDecimal("8");
	public static void main(String[] args){
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			String s = cin.next();
			ans = new BigDecimal("0");
			base = new BigDecimal("1");
			int len = s.length();
			for(int i = 2; i < len; i ++){
				base = base.divide(Eight);
				tmp = new BigDecimal(s.charAt(i) - '0');
				ans = ans.add(tmp.multiply(base));
			}
			System.out.println(s + " [8] = " + ans + " [10]");
		}
	}
}
