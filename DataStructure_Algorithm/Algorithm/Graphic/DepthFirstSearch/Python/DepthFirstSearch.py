#coding:utf-8
import Queue

vertex = [1,2,3,4,5]
color = [0,0,0,0,0]
distance = [0,0,0,0,0]
f = [0,0,0,0,0]
parent = [0,0,0,0,0]
vertexNum = 5
adjacentList = [
	[1,2,4],
	[0,2],
	[0,1,3,4],
	[2,4],
	[0,2,3]
]
time = 0
queue = Queue.Queue()

def DepthFirstSearch(s):
	for u in range(vertexNum):
		color[u] = 'WHITE'
		parent[u] = None
	for u in range(vertexNum):
		if color[u] == 'WHITE':
			DfsVisit(u)
		
def DfsVisit(u):
	global time
	color[u] = 'GRAY'
	time += 1
	distance[u] = time
	for v in adjacentList[u]:
		if color[v] == 'WHITE':
			parent[v] = u
			DfsVisit(v)
	color[u] = 'BLACK'
	print u
	time += 1
	f[u] = time
		
DepthFirstSearch(1)
print color
	