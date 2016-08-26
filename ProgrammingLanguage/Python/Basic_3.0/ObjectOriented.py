class Car:
	def __init__(self, c):   # Constructor
		self.__color = 'Red' # private field
		self.Color = c       # public property
	
	def __printColor(self):  # private method
		print(self.__color)
		
	def printColor(self):    # public method
		self.__printColor()

	color = 'Blue'           # static property of Class
		
	def getColor():          # static method of Class
		return Car.color
# end of Class Car

car1 = Car("Green")
print(Car.color)
print(car1.Color)
car1.printColor()
Car.price = 1000   # add static property of Class
car1.Price = 2000  # add property of Instance
print(Car.price)
print(car1.Price)

