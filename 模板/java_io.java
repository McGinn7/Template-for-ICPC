import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
	static final String file = "data";

	public static void main(String[] args) {
		Scanner in = null;
		PrintWriter out = null;
		try {
			in = new Scanner(new File(file + ".in"));
			// in = new Scanner(System.in);
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
