#coding:utf-8
import Queue

color = [0,0,0,0,0]
distance = [0,0,0,0,0]
parent = [0,0,0,0,0]
vertexNum = 5
adjacentList = [
	[1,2,4],
	[0,2],
	[0,1,3,4],
	[2,4],
	[0,2,3]
]
MAX_VALUE = 999999999
queue = Queue.Queue()

def BreadthFirstSearch(s):
	for u in range(vertexNum):
		color[u] = 'WHITE'
		distance[u] = MAX_VALUE
		parent[u] = None
	color[s] = 'GRAY'
	distance[s] = 0
	parent[s] = None
	queue.put(s)
	while queue.empty() == False:
		u = queue.get()
		for v in adjacentList[u]:
			if color[v] == 'WHITE':
				color[v] = 'GRAY'
				distance[v] = distance[u] + 1
				parent[v] = u
				queue.put(v)
		color[u] = 'BLACK'
		
def printPath(s,v):
	if v == s:
		print s
	elif parent[v] == None:
		print 'no path from %d to %d exists'%(s,v)
	else:
		printPath(s,parent[v])
		print v
		
BreadthFirstSearch(1)
printPath(1,4)
	
	