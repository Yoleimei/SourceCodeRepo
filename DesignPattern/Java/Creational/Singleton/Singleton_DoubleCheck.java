import java.util.Scanner;

public class Singleton_DoubleCheck {
    public static Singleton_DoubleCheck GetInstance() {
        if (uniqueInstance == null) {
            synchronized (Singleton_DoubleCheck.class) {
                if (uniqueInstance == null) {
                    uniqueInstance = new Singleton_DoubleCheck();
                }
            }
        }
        return uniqueInstance;
    }
	
	public void Test() {
		System.out.println("Enter your name:");
		Scanner s = new Scanner(System.in);
		String str = s.nextLine();
		System.out.println(str);
	}
	
	public static void main(String arg[]) {
		Singleton_DoubleCheck instance = Singleton_DoubleCheck.GetInstance();
		instance.Test();
	}
	
    private volatile static Singleton_DoubleCheck uniqueInstance;
    private Singleton_DoubleCheck() {}
}
