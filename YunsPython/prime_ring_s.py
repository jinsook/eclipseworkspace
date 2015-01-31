
import math, sys

def primenumbers(n):

	n = int(n)
	if n < 2:
		return []
	elif n == 2:
		return [2]

	ps = [2]; k = 3
	while k <= n:
		sqrtk = math.sqrt(k)
		for p in ps:
			if p > sqrtk:
				ps.append(k)
				break

			if not k % p:
				break
		k += 2

	return ps

def ifront(i,l):
	r = list(l)
	r.insert(0,i)
	return r

def prime_ring(n):

	primes = primenumbers(2*n) # generate prime numbers

	def prime_list(s,e,l):
		if len(l) == 0:
			return []
		elif len(l) == 1:
			if s+l[0] in primes and e + l[0] in primes:
				return [l]
			else:
				return []

		ll = []
		for i in l:
			llt = []
			if s+i in primes:
				lt = list(l)
				lt.remove(i)
				llt = prime_list(i,e,lt)
				llt = [ifront(i,a) for a in llt]
			ll.extend(llt)
		return ll

	ll = prime_list(1,1,range(2,n+1))
	ll = [ifront(1,l) for l in ll]

	for l in ll:
		print l

while True:
	sys.stdout.write('n? ')
	n = sys.stdin.readline()
	if n == '\n':
		break

	prime_ring(int(n))

