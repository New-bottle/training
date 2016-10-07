
def f():
	print 676
	for i in range(26):
		for j in range(26):
			print chr(i + ord('a')) + chr(j + ord('a'))

f()
