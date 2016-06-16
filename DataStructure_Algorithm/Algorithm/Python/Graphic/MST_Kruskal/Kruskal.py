#coding:utf-8
import sys

vertexNum = 9
adjacentList = []
edgeList = []
p = [0 for x in range(vertexNum)]
rank = [0 for x in range(vertexNum)]

class adjacentNode(object):
	def __init__(self,vertexIdx=-1,weight=0,next=None):
		self.vertexIdx = vertexIdx
		self.weight = weight
		self.next = next

class edge(object):
	def __init__(self,source,destination,weight):
		self.source = source
		self.destination = destination
		self.weight = weight
		
def compareEdgeWeight(edge1, edge2):
	if edge1.weight > edge2.weight:
		return 1
	elif edge1.weight == edge2.weight:
		return 0
	elif edge1.weight < edge2.weight:
		return -1
	else:
		pass
		
def MakeSet(x):
	p[x] = x
	rank[x] = 0
	
def Union(x,y):
	Link(FindSet(x),FindSet(y))
	
def Link(x,y):
	if rank[x] > rank[y]:
		p[y] = x
	else:
		p[x] = y
		if rank[x] == rank[y]:
			rank[y] = rank[y] + 1
			
def FindSet(x):
	if x != p[x]:
		p[x] = FindSet(p[x])
	return p[x]
	
def createAdjacentList():
	for i in range(vertexNum):
		adjacentList.append(adjacentNode(i))
		
def insertAdjacentNode(uNode,vertexIdx,weight):
	if uNode.next == None:
		uNode.next = adjacentNode(vertexIdx,weight)
	else:
		insertAdjacentNode(uNode.next,vertexIdx,weight)
		
def constructAdjacentList():
	# a-0  b-1  c-2  d-3  e-4  f-5  g-6  h-7  i-8
	insertAdjacentNode(adjacentList[0],1,4)
	insertAdjacentNode(adjacentList[0],7,8)
	insertAdjacentNode(adjacentList[1],2,8)
	insertAdjacentNode(adjacentList[1],7,11)
	insertAdjacentNode(adjacentList[2],3,7)
	insertAdjacentNode(adjacentList[2],5,4)
	insertAdjacentNode(adjacentList[2],8,2)
	insertAdjacentNode(adjacentList[3],4,9)
	insertAdjacentNode(adjacentList[3],5,14)
	insertAdjacentNode(adjacentList[4],5,10)
	insertAdjacentNode(adjacentList[5],6,2)
	insertAdjacentNode(adjacentList[6],7,1)
	insertAdjacentNode(adjacentList[6],8,6)
	insertAdjacentNode(adjacentList[7],8,7)
	
	insertAdjacentNode(adjacentList[1],0,4)
	insertAdjacentNode(adjacentList[7],0,8)
	insertAdjacentNode(adjacentList[2],1,8)
	insertAdjacentNode(adjacentList[7],1,11)
	insertAdjacentNode(adjacentList[3],2,7)
	insertAdjacentNode(adjacentList[5],2,4)
	insertAdjacentNode(adjacentList[8],2,2)
	insertAdjacentNode(adjacentList[4],3,9)
	insertAdjacentNode(adjacentList[5],3,14)
	insertAdjacentNode(adjacentList[5],4,10)
	insertAdjacentNode(adjacentList[6],5,2)
	insertAdjacentNode(adjacentList[7],6,1)
	insertAdjacentNode(adjacentList[8],6,6)
	insertAdjacentNode(adjacentList[8],7,7)
		
def printAdjacentList():
	for i in range(vertexNum):
		node = adjacentList[i]
		sys.stdout.write('%d'%node.vertexIdx)
		while node.next != None:
			sys.stdout.write('->%d(%d)'%(node.next.vertexIdx,node.next.weight))
			node = node.next
		sys.stdout.write('\n')
			
def createEdgeList():
	for u in range(vertexNum):
		uNode = adjacentList[u].next
		while uNode != None:
			v = uNode.vertexIdx
			w = uNode.weight
			if u < v:
				minIdx,maxIdx = u,v
			else:
				minIdx,maxIdx = v,u
			insertEdge(minIdx,maxIdx,w)
			uNode = uNode.next
				
def insertEdge(u,v,w):
	l = len(edgeList)
	hasEdge = False
	for e in edgeList:
		if e.source == u and e.destination == v:
			hasEdge = True
			break
	if hasEdge == False:
		edgeList.append(edge(u,v,w))
		
def sortEdgeList():
	edgeList.sort(compareEdgeWeight)
		
def printEdgeList():
	l = len(edgeList)
	for e in edgeList:
		print 'weight(%d,%d)=%d'%(e.source,e.destination,e.weight)
			
def MST_Kruskal():
	for v in range(vertexNum):
		MakeSet(v)
	edgeNum = len(edgeList)
	for e in range(edgeNum):
		newEdge = edgeList[e]
		if FindSet(newEdge.source) != FindSet(newEdge.destination):
			Union(newEdge.source, newEdge.destination)
			s,d,w = newEdge.source,newEdge.destination,newEdge.weight
			print 'KruskalEdge(%d,%d),weight=%d'%(s,d,w)
			
createAdjacentList()
constructAdjacentList()
createEdgeList()
sortEdgeList()
printAdjacentList()
printEdgeList()
MST_Kruskal()
