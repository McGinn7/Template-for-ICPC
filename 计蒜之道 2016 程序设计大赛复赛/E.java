import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	static BigInteger val(int value) {
		return BigInteger.valueOf(value);
	}

	public static void main(String[] args) throws FileNotFoundException {
		Scanner in = new Scanner(System.in);
		BigInteger n = in.nextBigInteger();
		if (n.mod(val(3)).equals(BigInteger.ZERO)) {
			n = n.divide(val(3));
			System.out.println(n + " " + n + " " + n);			
		} else {
			System.out.println("-1");
		}
	}
}