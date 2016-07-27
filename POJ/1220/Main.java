import java.math.*;
import java.util.*;

public class Main{
	static BigInteger ori, t;
	static BigInteger Zero = new BigInteger("0");
	static BigInteger Ten = new BigInteger("10");
	static BigInteger Base;
	static String in, out;
	static Map<char, int> get = new HashMap<char, int>();
	static Map<int, char> c = new HashMap<int, char>();
	static int prebase, targetbase, testcase;
	public static void main(String[] args){
		for(int i = 0; i < 9; i ++){
			c.put(i, i + '0');
			get.put(i + '0', i);
		}
		for(int i = 0; i < 26; i ++){
			c.put(i + 10, i + 'A');
			c.put(i + 36, i + 'a');
			get.put(i + 'A', i + 10);
			get.put(i + 'a', i + 36);
		}
		Scanner cin = new Scanner(System.in);
		testcase = cin.nextInt();
		while(testcase > 0){
			testcase --;
			ori = Zero;
			prebase = cin.nextInt();
			Base = BigInteger.valueOf(prebase);
			targetbase = cin.nextInt();
			in = cin.next();
			int len = in.length(), val;
			for(int i = len - 1; i >= 0; i --){
				val = get.get(in.charAt(i));
				t = BigInteger.valueOf(val);
				ori = (ori.multiply(Base)).add(t);
			}
			Base = BigInteger.valueOf(targetbase);
			int i = 0;
			out = new String("");
			while(ori.compareTo(Zero) != 0){
				out = out + (c.get(ori.mod(Base)));
				ori = ori.divide(Base);
				i ++;
			}
			StringBuffer tmp = new StringBuffer(out);
			tmp.reverse();
			System.out.println(prebase + " " + in);
			System.out.println(targetbase + " " + tmp);
		}
	}
}
