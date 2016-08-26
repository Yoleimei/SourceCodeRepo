import math

# return one value
def myAdd(x, y):
	return x + y
ret = myAdd(1, 2)
print(ret)
	
# return tuple
def myMaxMin(x, y):
	return max(x, y), min(x, y)
retMax, retMin = myMaxMin(1, 2)
print("Max:", retMax, ",", "Min", retMin)

# default params
def myPower(x, n=2):
	return x**n
print(myPower(5))
print(myPower(5, 3))
print(myPower(n=4, x=5))

# variable params
def mySum(num1, num2=2, *num):
	sum = num1 + num2
	for n in num:
		sum = sum + n
	return sum
print(mySum(1))
print(mySum(1,2))
print(mySum(1,2,3))
print(mySum(1,2,3,4))

# key-value params
def person(name, age=25, *hobby, **other):
	if (0 == len(hobby)):
		print("name:",name,"age",age)
	elif (0 == len(other)):
		print("name:",name,"age",age,"hobby:",hobby)
	else:
		print("name:",name,"age",age,"hobby:",hobby,"other:",other)
	return
person("yoleimei")
person("yoleimei", 26)
person("yoleimei", 26, "Programming", "Game")
person("yoleimei", 26, "Programming", "Game", height=175, weight=120)
