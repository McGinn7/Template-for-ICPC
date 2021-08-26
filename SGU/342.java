import java.util.Scanner;
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);

        BigInteger A = in.nextBigInteger();
        BigInteger B = in.nextBigInteger();
        final int b = B.intValue();

        if (1 == b) {
            out.println(A);
        } else {
            int L = 0, G = 100000000;
            while (A.compareTo(BigInteger.ZERO) > 0) {
                BigInteger[] ret = A.divideAndRemainder(B);
                int r = ret[1].intValue();
                int l = Math.min(L + r, G + r + 1);
                int g = Math.min(L + b - r, G + b - r - 1);
                L = l;
                G = g;
                A = ret[0];
            }
            int ans = Math.min(L, G + 1);
            out.println(ans);
        }

        in.close();
        out.close();
    }

}
