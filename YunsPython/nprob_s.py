
import sys

table = {}

def cl(N,pr=False):

	(i,n,cnt,nlist) = (0,N,0,[])

	while n > 1:
		nlist.append(n)

		if table.has_key(n):
			i += table[n]
			break

		if n % 2 == 0:
			n = n/2
		else:
			n = 3*n+1
		i = i + 1
		cnt = cnt + 1 # count

	table[N] = i

	if len(nlist):
		k = table[nlist.pop()]
		while len(nlist) > 0:
			k += 1
			table[nlist.pop()] = k

	return (i+1,cnt)

def maxcl(a,b):
	l = map(cl,range(a,b+1))
	return max(l)

#inputs = [[1,10],[100,200],[201,210],[900,1000],[1,100000]]
inputs = [[1,10],[100,200],[201,210],[900,1000]]

CNT = 0
for input in inputs:
	(s,e) = (input[0],input[1])
	(mc, cnt) = maxcl(s,e)
	CNT = CNT + cnt
	print s, e, mc

print 'The number of calculations =', CNT

sys.stdin.readline()

