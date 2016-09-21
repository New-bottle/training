import random
import sys


def f():

	N = 1000
	Q = 1000
	ls = 0
	sigma = 0
	print N, Q
	s = ""
	for i in range(N):
		m = 1
		M = 0
		if ls < N / 2:
			m = 0
		if sigma > 0:
			M = 1
		a = random.randint(m, M)
		if a == 0:
			s += '('
			ls += 1
			sigma += 1
		else:
			s += ')'
			sigma -= 1
	print s
	for i in range(Q):
		print random.randint(1, N)

f()
