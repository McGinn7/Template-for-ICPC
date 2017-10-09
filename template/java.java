import java.io.File;
import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	/**
	* Compile: javac Main.java
	* Run: java Main 
	*/

	/**
	 * Functions of BigInteger
	 * add、subtract、multiply、divide、mod、pow、modPow
	 * BigInteger[] divideAndRemainder(BigInteger val)
	 * BigInteger modPow(BigInteger exponent, BigInteger m)
	 * modInverse(BigInteger mod) - 逆元，需互质
	 */

	/**
	 * Functions of BigDecimal
	 * BigDecimal divide(BigDecimal divisor, int scale, RoundingMode roundingMode)
	 * RoundingMode: ROUND_HALF_[DOWN|UP|EVEN], ROUND_FLOOR, ROUND_CEILING
	 * BigDecimal negate(): return value is (-this)
	 * BigDecimal setScale(int newScale, [int roundingMode]): 保留小数位数
	 */

	Main() throws Exception {
		Scanner in = null;
		PrintWriter out = null;
		// standard input/output
		in = new Scanner(System.in);
		out = new PrintWriter(System.out);
		// file input/output
		in = new Scanner(new File("input.txt"));
		out = new PrintWriter(new File("output.txt"));
		/**
		 * in.next[Type]() , Type = Int, Long, Double, BigInteger
		 * out.println([String])
		 */
		// multiple testcases
		while (in.hasNext()) {
			// TODO
		}
		// Note: must close file!
		in.close();out.close();
	}

	public static void main(String[] args) throws Exception {
		new Main();
	}
}
