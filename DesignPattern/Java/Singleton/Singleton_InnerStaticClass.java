import java.util.Scanner;

public class Singleton_InnerStaticClass {
    public static Singleton_InnerStaticClass GetInstance() {
        return SingletonHolder.INSTANCE;
    }
	
	public void Test() {
		System.out.println("Enter your name:");
		Scanner s = new Scanner(System.in);
		String str = s.nextLine();
		System.out.println(str);
	}
	
	public static void main(String arg[]) {
		Singleton_InnerStaticClass instance = Singleton_InnerStaticClass.GetInstance();
		instance.Test();
	}
	
	private Singleton_InnerStaticClass() {}
	
    private static class SingletonHolder {
		private static final Singleton_InnerStaticClass INSTANCE = new Singleton_InnerStaticClass();
	}
}
