import java.math.*;
import java.util.*;

public class Main{
	static BigInteger ori, t;
	static BigInteger Zero = new BigInteger("0");
	static BigInteger Ten = new BigInteger("10");
	static BigInteger Base;
	static String in, out;
	static Map<Character, Integer> get = new HashMap<Character, Integer>();
	static Map<Integer, Character> c = new HashMap<Integer, Character>();
	static int prebase, targetbase, testcase;
	public static void main(String[] args){
		for(int i = 0; i < 10; i ++){
			c.put(i, (char)(i + (char)'0'));
			get.put((char)(i + '0'), i);
		}
		for(int i = 0; i < 26; i ++){
			c.put(i + 10, (char)(i + 'A'));
			c.put(i + 36, (char)(i + 'a'));
			get.put((char)(i + 'A'), i + 10);
			get.put((char)(i + 'a'), i + 36);
		}
		
		/*
		Set<Character> test = get.keySet();
		for(Character t : test){
			System.out.println(t + " , " + get.get(t));
		}
		*/
		
		Scanner cin = new Scanner(System.in);
		testcase = cin.nextInt();
		while(testcase > 0){
			testcase --;
			ori = Zero;
			prebase = cin.nextInt();
			Base = BigInteger.valueOf(prebase);
			targetbase = cin.nextInt();
			in = cin.next();
			Integer len = in.length(), val;

			for(int i = 0; i < len; i ++){
				val = get.get(in.charAt(i));
				t = BigInteger.valueOf(val);
				ori = (ori.multiply(Base)).add(t);
			}//ok

			Base = BigInteger.valueOf(targetbase);
			Integer i;
			out = new String("");
			if (ori.compareTo(Zero) == 0){
				out = out + "0";
			}
			while(ori.compareTo(Zero) != 0){
				i = ori.mod(Base).intValue();
				out = out + (c.get(i));
				ori = ori.divide(Base);
				i ++;
			}
			StringBuffer tmp = new StringBuffer(out);
			tmp.reverse();
			System.out.println(prebase + " " + in);
			System.out.println(targetbase + " " + tmp);
			if (testcase > 0) System.out.println();
		}
	}
}
