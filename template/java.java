import java.io.File;
import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	/**
	 * 大数常用操作
	 * add、subtract、multiply、divide、mod、pow、modPow
	 * modInverse(BigInteger mod) - 逆元，需互质
	 */

	Main() throws Exception {
		Scanner in = null;
		PrintWriter out = null;
		// 标准输入输出
		in = new Scanner(System.in);
		out = new PrintWriter(System.out);
		// 文件输入输出
		in = new Scanner(new File("input.txt"));
		out = new PrintWriter(new File("output.txt"));
		/**
		 * in.next[Type]() , Type = Int, Long, Double, BigInteger
		 * out.println([String])
		 */
		// Note: must close file!
		in.close();out.close();
	}

	public static void main(String[] args) throws Exception {
		new Main();
	}
}
