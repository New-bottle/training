//learn java from the code of team Gungnir
import java.math.*;
import java.util.*;

public class Main{
	static int LEN = 1_000_000;
	static BigInteger n, m;
	static BigInteger Zero = new BigInteger("0");
	static BigInteger One = new BigInteger("1");
	static BigInteger Two = new BigInteger("2");
	static BigInteger[] queue = new BigInteger[LEN];
	static BigInteger[] num_step = new BigInteger[LEN];
	static Collection c = new HashSet();
	public static void main(String[] args){
		Scanner cin = new Scanner(System.in);
		while(true){
			n = cin.nextBigInteger();
			m = cin.nextBigInteger();
			if (n.compareTo(Zero) == 0 && m.compareTo(Zero) == 0) break;
			BigInteger ans = (n.subtract(m)).abs();
			c.clear();
			c.add(n);
			int head = 1, tail = 1;
			queue[1] = n;
			num_step[1] = Zero;
			BigInteger x, tmp, now, p;
			while(head <= tail){
				x = queue[head];
				now = num_step[head ++];
				tmp = (x.subtract(m).abs()).add(now);
				if (ans.compareTo(tmp) > 0) ans = tmp;
				now = now.add(One);
				if ((x.mod(Two)).compareTo(Zero) == 0){
					p = x.divide(Two);
					if (c.contains(p) == false){
						c.add(p);
						queue[++ tail] = p;
						num_step[tail] = now;
					}
				}else{
					p = x.add(One);
					if (c.contains(p) == false){
						c.add(p);
						queue[++ tail] = p;
						num_step[tail] = now;
					}
					p = x.subtract(One);
					if (c.contains(p) == false){
						c.add(p);
						queue[++ tail] = p;
						num_step[tail] = now;
					}
				}
			}
			System.out.println(ans);
		}
	}
}


