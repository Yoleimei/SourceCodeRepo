#coding:utf-8
import sys

MAX_VALUE = 999999999
vertexNum = 5

d = [0,0,0,0,0]
pre = [0,0,0,0,0]
visited = [False,False,False,False,False]
adjacentMatrix = [
	[ 0,10, 0, 5, 0],
	[ 0, 0, 1, 2, 0],
	[ 0, 0, 0, 0, 4],
	[ 0, 3, 9, 0, 2],
	[ 7, 0, 6, 0, 0]
]

def InitializeSingleSource(s):
	for u in range(vertexNum):
		d[u] = MAX_VALUE
		pre[u] = None
	d[s] = 0

def ExtractMin():
	distance = MAX_VALUE
	m = -1
	for u in range(vertexNum):
		if visited[u] == False and d[u] < distance:
			distance = d[u]
			m = u
	return m
	
def Relax(u,v,w):
	if d[v] > d[u] + w:
		d[v] = d[u] + w
		pre[v] = u
		
def Dijkstra(s):
	InitializeSingleSource(s)
	print d
	for i in range(vertexNum):
		u = ExtractMin()
		visited[u] = True
		for v in range(vertexNum):
			if adjacentMatrix[u][v] > 0 and visited[v] == False:
				Relax(u,v,adjacentMatrix[u][v])
				
def PrintPath(s):
	if pre[s] == None:
		sys.stdout.write('%d'%s)
	else:
		PrintPath(pre[s])
		sys.stdout.write('-->%d'%s)
		
Dijkstra(1)
print d
print visited
print pre
PrintPath(0)
print ' '
PrintPath(2)
print ' '
PrintPath(3)
print ' '
PrintPath(4)
print ' '
				