import time
start_time = time.time()

start_A = 873
start_B = 583

fac_A = 16807
fac_B = 48271
mod_fac = 2147483647

count = 0

cur_A = start_A
cur_B = start_B

for i in range(40000000):
    cur_A = (cur_A * fac_A) % mod_fac
    cur_B = (cur_B * fac_B) % mod_fac
    
    count += (cur_B & 0xFFFF) == (cur_A & 0xFFFF)

print("Part 1: " + str(count))
    

print("--- %s seconds ---" % (time.time() - start_time))