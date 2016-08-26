import java.util.Scanner;

public class BasicIOTest {
	public static void main(String arg[]) {
		System.out.println("Enter your name:");
		Scanner s = new Scanner(System.in);
		String str = s.nextLine();
		System.out.println(str);
	}
}
