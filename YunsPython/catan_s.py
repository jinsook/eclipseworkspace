
import sys, copy

def returnExtend(x,y):
	z = copy.deepcopy(x)
	z.extend(y)
	return z

def formRoad(network):
	nw = copy.deepcopy(network)

	numEdges = len(nw)

	numNodes = max(reduce(lambda x,y: returnExtend(x,y), nw))+1

	road = [[None for col in range(numNodes)] for row in range(numNodes)]

	roadNum = 1
	for col in range(numNodes):
		for row in range(numNodes):
			if [col,row] in nw or [row,col] in nw:
				(road[col][row], road[row][col]) = (roadNum,roadNum)
				roadNum += 1

	paths = [[[0 for col in range(numNodes)] for row in range(numNodes)] for depth in range(numEdges)]

	return (road, paths, numNodes, numEdges)


class path:
	def __init__(self,s,e,road):
		(self.s, self.e, self.road) = (s,e,road)

		if s == e:
			(self.nodes,self.edges) = ([s],[])
		else:
			if road[s][e]:
				(self.nodes,self.edges) = ([s,e], [road[s][e]])
			else:
				(self.nodes,self.edges) = ([s],[])

		self.arrow = ' -> '

	def overlap(self,p):
		return any(map(lambda x:x in self.edges,p.edges))

	def extend(self,p):
		self.nodes.extend(p.nodes[1:])
		self.edges.extend(p.edges)
		e = self.nodes[-1]

	def len(self):
		return len(self.edges)

	def __repr__(self):
		if self.nodes:
			s = str(self.s)
			for i in range(len(self.edges)):
				s += self.arrow + str(self.nodes[i+1])

			if self.len():
				s += ' [' + str(self.len()) + ']'
			else:
				s += ' [0]'

			return s

def printpaths(paths,name=None):
	n = len(paths)

	print name + ':'
	for i in range(n-1):
		for j in range(i,n):
			print (i,j), paths[i][j]


def updatePaths(paths,i):
	n = len(paths[0])
	(prev_paths,next_paths) = (paths[i],paths[i+1])

	maxLenO = 0
	for i in range(n):
		for j in range(n):
			maxp = prev_paths[i][j]
			maxLen = maxp.len()
			for k in range(n):
				if i !=j and i !=k and j != k:
					(p1,p2) = (prev_paths[i][k],prev_paths[k][j])
					if p1.len() and p2.len():
						if not p1.overlap(p2):
							if p1.len()+p2.len() > maxLen:
								maxp = copy.deepcopy(p1)
								maxp.extend(p2)
								maxLen = maxp.len()
			next_paths[i][j] = maxp
			if maxLen > maxLenO:
				(maxpO,maxLenO) = (maxp,maxLen)

	return maxpO

if True:
	network = [ [0,2], [1,2], [2,3], [3,4], [3,5], [4,6], [5,7], [6,8], [7,8], [7,9], [8,10], [9,11], [10,12], [11,12], [10,13], [12,14] ]
else:
	network = [[0,1],[1,2]]

(road, paths, numNodes, numEdges) = formRoad(network)

for s in range(numNodes):
	for e in range(numNodes):
		paths[0][s][e] = path(s,e,road)

for i in range(numEdges-1):
	mpath = updatePaths(paths,i)
	if mpath.len() == numEdges or paths[i+1] == paths[i]:
		break

print 'Found after', i+2, 'iteration(s)!'
print 'The length of the longest road is', mpath.len()
print 'The longest road is', mpath

sys.stdin.readline()

