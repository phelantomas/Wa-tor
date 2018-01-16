import os
import time

loop_times = 100
start_time = time.time()
for i in range(loop_times):
	os.system('/home/tomas/Wa-tor/Wa-tor/DangerZone')
end_time = time.time()

print("Total time taken this loop: ", end_time - start_time)
print("Average time taken through this loop: ", (end_time - start_time) / loop_times)




