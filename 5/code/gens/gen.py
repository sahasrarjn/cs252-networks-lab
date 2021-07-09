import sys

A = []
for i in range(int(sys.argv[1])):
	a = input()
	if i%2==1:
		A.append(a)

print(A)
