import os

#need to change paths to work for you
for i in range(2):
	os.system('/home/tomas/Wa-tor/Wa-tor/DangerZone')

with open("runtime.txt") as f:
	content = f.readlines()

#Delete file after reading it
os.remove('/home/tomas/Wa-tor/Wa-tor/runtime.txt')

content = [x.strip() for x in content]

content = [float(i) for i in content]

with open("averageRuntime.txt", 'a') as f:
	f.write(str(sum(content) / float(len(content))))
	

print("The average runtime is ", sum(content) / float(len(content)))


