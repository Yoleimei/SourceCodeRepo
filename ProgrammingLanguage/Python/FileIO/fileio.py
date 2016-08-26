#!/usr/bin/python

fp = open('./test.txt', 'w')
fp.write('Hello world!')
fp.close()

fp = open('./test.txt', 'r')
ret = fp.readline()
print(ret)
