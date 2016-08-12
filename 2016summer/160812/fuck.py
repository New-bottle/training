import random
N = 2000
print N
s = set()
R = 45
for i in range(N):
	while True:
		a = random.randint(1, R)
		b = random.randint(1, R)
		if not (a, b) in s:
			break
	s.add((a, b))
	print a, b
