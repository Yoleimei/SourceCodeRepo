public class Client {
	public static void main(String[] args) {
		ICreator creator = new Creator();
		IProduct product = creator.CreatorProduct();
		product.Print();	
	}
}
