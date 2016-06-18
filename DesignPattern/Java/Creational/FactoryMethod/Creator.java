public class Creator implements ICreator {
	public IProduct CreatorProduct() {
		return new Product();
	}
}
