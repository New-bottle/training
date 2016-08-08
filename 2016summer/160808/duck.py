import random

T = 5

print T

def f():
	N = 200000

	print N
	for i in range(N):
		print random.randint(0, 100000),
	print

for i in range(T):
	f()
