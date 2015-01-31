
import sys

def returnExtend(x,y):
	z = x
	z.extend(y)
	return z

def returnAppend(a,l):
	return returnExtend(list(a),l)

def allcomb(l):
	assert len(l)
	if len(l) is 1:
		return [l]

	lrst = []
	s = set()
	for i in range(len(l)):
		if l[i] in s:
			continue
		a = l[:i]
		a.extend(l[i+1:])

		lsub = allcomb(a)
		lnew = map( lambda x: returnAppend(l[i],x), lsub)
		lrst.extend(lnew)
		s.add(l[i])

	return lrst

words = ['aAb','abc','acba']
#words = ['abca']

for word in words:
	l = list(word)
	l.sort()
	l = map(lambda x: ''.join(x), allcomb(l))
	for w in l:
		print w

sys.stdin.readline()

