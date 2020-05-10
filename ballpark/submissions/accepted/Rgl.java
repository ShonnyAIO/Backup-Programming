public class Rgl {
  public static void main(String[] args) {
    long n = new java.util.Scanner(System.in).nextLong();
    long p = 1;
    double nf = (double) n;
    while (n >= 10) {
      nf /= 10;
      n /= 10;
      p *= 10;
    }
    n = Math.round(nf);
    System.out.println(n * p);
  }
}
