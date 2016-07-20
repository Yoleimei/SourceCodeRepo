#coding:utf-8
vertex = [
	'shirt',
	'tie',
	'jacket',
	'belt',
	'watch',
	'undershorts',
	'pants',
	'shoes',
	'socks'
]
adjacentList = [
	[1,3], # shirt
	[2], # tie
	[], # jacket
	[2], # belt
	[], # watch
	[6,7], # undershorts
	[3,7], # pants
	[], # shoes
	[7] # socks
]
MAX_VALUE = 999999999
vertexNum = 9
time = 0
color = [0 for x in range(vertexNum)]
parent = [0 for x in range(vertexNum)]
distance = [0 for x in range(vertexNum)]
timestampBegin = [0 for x in range(vertexNum)]
timestampEnd = [0 for x in range(vertexNum)]
dressScheduling = []

def DepthFirstSearch():
	for u in range(vertexNum):
		color[u] = 'white'
		parent[u] = None	
	for u in range(vertexNum-1,-1,-1):	
		DfsVist(u)
	
def DfsVist(u):
	global time
	if color[u] == 'black':
		return
	print '%d turns gray'%u
	color[u] = 'gray'
	time += 1
	timestampBegin[u] = time
	distance[u] = time
	for v in adjacentList[u]:
		if color[v] == 'white':
			parent[v] = u
			print 'DfsVist(%d)'%v
			DfsVist(v)
	time += 1
	timestampEnd[u] = time
	color[u] = 'black'
	print '%d turns black'%u
	dressScheduling.append(vertex[u])
		
def printScheduling():
	global dressScheduling
	dressScheduling = list(reversed(dressScheduling))
	print dressScheduling
	
DepthFirstSearch()
print timestampBegin
print timestampEnd
printScheduling()
