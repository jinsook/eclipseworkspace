
import sys

class PP:
	'''parallelepiped class'''

	def __init__(self,x1=0,y1=0,z1=0,x2=0,y2=0,z2=0):
		if x1 >= x2 or y1 >= y2 or z1 >= z2:
			self.em = True
			self.vol = 0
			return

		(self.x1,self.x2,self.y1,self.y2,self.z1,self.z2) = (x1,x2,y1,y2,z1,z2)
		self.em = False
		self.vol = (self.x2-self.x1)*(self.y2-self.y1)*(self.z2-self.z1)

	def intersect(self,other):
		if self.em or other.em:
			return PP()

		return PP(
		max(self.x1,other.x1),max(self.y1,other.y1),max(self.z1,other.z1),
		min(self.x2,other.x2),min(self.y2,other.y2),min(self.z2,other.z2))

	def __and__(self,other):
		return self.intersect(other)


	def __repr__(self):
		if self.em:
			return '()'

		return ( '(' + str(self.x1) + ',' + str(self.y1) + ',' + str(self.z1) + ')'
				+ '-(' + str(self.x2) + ',' + str(self.y2) + ',' + str(self.z2) + ')'
				+ '; (' + str(self.vol) + ')' )

def binarylist(n):
	assert n > 0
	if n > 1:
		def returnAppended(a,x):
			y = [a]
			y.extend(x)
			return y

		l = binarylist(n-1)
		l0 = map(lambda x: returnAppended(0,x),l)
		l1 = map(lambda x: returnAppended(1,x),l)

		l0.extend(l1)
		return l0
	else:
		return [[0],[1]]


def overlapvol(s):
	n = len(s)
	assert n > 1

	v = 0
	bl = binarylist(n)
	for idxs in bl:
		num = sum(idxs)
		if num < 2:
			continue
		p = reduce(lambda x,y: x.intersect(y), [s[i] for i in range(n) if idxs[i]])
		if not p.em:
			#print p, pow(-1,num)*(num-1)
			v += pow(-1,num)*(num-1)*p.vol

	return v

if __name__ == "__main__":

	s = [ PP(1,1,1,3,3,3),
			PP(1,1,1,3,3,3),
			PP(1,1,1,3,3,3),
			PP(400000000,400000000,400000000,400000001,400000001,400000002),
			PP(400000000,400000000,400000000,400000002,400000004,400000001) ]

	print str(len(s)), 'parallelepipeds:'
	for i in range(len(s)):
		print s[i]

	print ''
	print 'The volume of intersecting parallelepipeds =', overlapvol(s)

	sys.stdin.readline()

