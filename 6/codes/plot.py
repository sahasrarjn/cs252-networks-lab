import matplotlib.pyplot as plt 
import numpy
import math

f = open("final.txt",'r')

delays = [10, 50, 100]
losses = [0.1, 0.5, 1]

mu_cubic = [ [0 for i in range(0,3)] for j in range(0,3)]
sd_cubic = [ [0 for i in range(0,3)] for j in range(0,3)]

mu_reno  = [ [0 for i in range(0,3)] for j in range(0,3)]
sd_reno  = [ [0 for i in range(0,3)] for j in range(0,3)]

i=-1
j=-1
c=0

for l in f:
	if(l[0] == "C"):
		c = 1
	elif(l[0] == "R"):
		c = 0
	elif(l[0] == "D"):
		j+=1
	elif(l[0] == "L"):
		i+=1
		i = i%3
	elif(l[0] == "M"):
		if c==0:
			mu_reno[i][j] = float(l.split(':')[1].rstrip("\n"))
		else:
			mu_cubic[i][j] = float(l.split(':')[1].rstrip("\n"))
	elif(l[0] == "S"):
		if c==0:
			sd_reno[i][j] = float(l.split(':')[1].rstrip("\n"))
		else:
			sd_cubic[i][j] = float(l.split(':')[1].rstrip("\n"))
	else:
		continue

mu_cubic = numpy.array(mu_cubic)
sd_cubic = numpy.array(sd_cubic)

mu_reno = numpy.array(mu_reno)
sd_reno = numpy.array(sd_reno)


for i in range(0,3):
	fig = plt.figure()
	plt.errorbar(delays, mu_cubic[:][i], yerr=(1.64/math.sqrt(20))*sd_cubic[:][i],label='cubic')
	plt.errorbar(delays, mu_reno[:][i], yerr=(1.64/math.sqrt(20))*sd_reno[:][i],label='reno')
	plt.title('Error = %0.1f%%' %losses[i])
	plt.grid()
	plt.xlabel("Delay (in ms)")
	plt.ylabel("Throughput (in bps)")
	plt.legend(loc='upper right')
	plt.savefig('Plot %i' %(i+1))

for i in range(0,3):
	fig = plt.figure()
	plt.errorbar(losses, mu_cubic[i][:], yerr=(1.64/math.sqrt(20))*sd_cubic[i][:],label='cubic')
	plt.errorbar(losses, mu_reno[i][:], yerr=(1.64/math.sqrt(20))*sd_reno[i][:],label='reno')
	plt.title('Delay = %i ms' %delays[i])
	plt.grid()
	plt.xlabel("Loss (in %)")
	plt.ylabel("Throughput (in bps)")
	plt.legend(loc='upper right')
	plt.savefig('Plot %i' %(i+4))



