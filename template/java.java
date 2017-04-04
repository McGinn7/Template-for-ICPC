import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	static final String file = "data";

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
			System.out.println("out content");
			// 文件输入输出
			in = new Scanner(new File(file + ".in"));
			out = new PrintWriter(new File(file + ".out"));
		} catch (Exception e) {
			e.printStackTrace();
		}
		/**
		 * solve
		 */
		in.close();
		out.close();
	}
}
