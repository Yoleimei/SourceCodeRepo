#!/usr/bin/python

fp = open('./test.txt', 'w')
fp.write('Hello world!\n')
fp.write('Hello yoleimei!\n')
fp.close()

fp = open('./test.txt', 'r')
ret = fp.readline()
print(ret)

fp = open('./test.txt', 'r')
ret = fp.readlines()
for i in ret:
	print(i)
