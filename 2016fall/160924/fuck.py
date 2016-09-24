import random

def f():
	N = random.randint(1, 3000)
	print N
	for i in range(N):
		a = random.randint(0, 1048576)
		#a = 0
		print a,
	print
	for i in range(N):
		a = random.randint(0, 1048576)
		#a = 0
		print a,
	print

T = 2
print T
for i in range(T):
	f()
