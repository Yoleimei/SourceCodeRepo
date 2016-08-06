from functools import reduce

## Closure: return function
print("closure:")
def funFactory(str):
	def studyTiming(start, end):
		print(str,"study time:",start," ~",end)
	return studyTiming
# end of funFactory
highStudyTiming = funFactory("High School")
highStudyTiming(2009, 2013)
middleStudyTiming = funFactory("Middle School")
middleStudyTiming(2006, 2009)

## Self Defined
print("Self Defined:")
def myPlus(x, y):
	return x + y
# end of myAdd

def myMinus(x, y):
	return x - y
# end of myMinus

def myFun(x, y, fun):
	return fun(x, y)
# end of myFun
	
x = 5
y = 4
x = myFun(x, y, myPlus)  # x = 9
print(x)
x = myFun(x, y, myMinus) # x = 5
print(x)


## map
print("map:")
def myMap(fun, seq):
	ret = []
	for x in seq:
		ret.append(fun(x))
	return ret
# end of myMap
list1 = list(range(1,5))
print("list1:",list1)
list2 = list(map(lambda x: x*x, list1))
print("list2:", list2)
list3 = list(myMap(lambda x: x*x, list1))
print("list3:", list3)

## reduce
print("reduce:")
def myReduce(fun, seq):
	vReduce = 0
	if (len(seq) < 2):
		return
	vReduce = fun(seq[0], seq[1])
	for x in seq[2:]:
		vReduce = fun(vReduce, x)
	return vReduce
# end of myReduce
list1 = list(range(1,5))
sum = reduce(lambda x,y: x+y, list1)
print("sum:", sum)
sum = myReduce(lambda x,y: x+y, list1)
print("sum:", sum)

## filter: remaining if Ture, and filtered if False
print("filter:")
def myFilter(fun, seq):
	ret = []
	for x in seq:
		if fun(x):
			ret.append(x)
	return ret
# end of myFilter
list1 = list(range(1,5))
print("list1:", list1)
list2 = list(filter(lambda x: (x%2)==0, list1))
print("list2:", list2)
list3 = list(myFilter(lambda x: (x%2)==0, list1))
print("list3:", list3)
