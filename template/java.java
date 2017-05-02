import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	
	public static void main(String[] args) {
		/**
		 * 大数常用操作
		 * add、subtract、multiply、divide、mod、pow、modPow
		 * modInverse(BigInteger mod) - 逆元，需互质
		 */
		Scanner in = null;
		PrintWriter out = null;
		try {
			// 标准输入输出
			in = new Scanner(System.in);
			// 文件输入输出
			in = new Scanner(new File("input.txt"));
			out = new PrintWriter(new File("output.txt"));
			// in.nextInt(), in.nextBigInteger() 
			// System.out.println([String]), out.println([String])
		} catch (Exception e) {
		}
		/**
		 * note: must close file!
		 */
		in.close();
		out.close();
	}
}
