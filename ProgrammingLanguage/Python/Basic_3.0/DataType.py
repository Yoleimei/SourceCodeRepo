
myRange = range(2, 6)

# List
myList = list(myRange)
myList.insert(0, 1)
myList.append(6)
myList.pop(1)
print(type(myList))
print(myList)

# Tuple
myTuple = tuple(myRange)
print(type(myTuple))
print(myTuple)

# Set
mySet = set(myRange)
mySet.add(6)
mySet.remove(2)
print(type(mySet))
print(mySet)

# Dict
myDict = { 'a':0, 'b':1, 'c':2 }
myDict['d'] = 3
myDict.pop('a')
print(type(myDict))
print(myDict)
