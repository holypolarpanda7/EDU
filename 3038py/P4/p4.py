# Greg Wagner
# Python 3038 ~Dr. Butler
# p4.py Multiprocessing program that breaks up the prime numbers problem for a given range (lo>=2 to hi) -6/14/18

from p4primetest import is_prime   # is_prime(n) where n is to be checked
import sys, time, math
import multiprocessing as mp

def worker(l, h, q):               # worker function that totals the number of primes in a range
    pQ = 0
    for n in range(l, h+1):
        if is_prime(n) == True:
            pQ += 1
    # print(mp.current_process().name, l, h, pQ)
    q.put(pQ)

# print("cpu_count: ",mp.cpu_count())  ## just for demo

procs = []
q = mp.Queue()
n = int(sys.argv[3])
lo = int(sys.argv[1])
hi = int(sys.argv[2])
r = (((hi+1)-lo) % n)
chunk = math.floor(((hi+1)-lo) / n)
bump = 0

for i in range(n):            # seperates full range into sub ranges as evenly as possible and hands off subranges
                              #             to worker functions that are then queued
    pl = math.floor(i * chunk + lo + bump)
 
    if i >= (n-r):
        bump += 1
             
    ph = math.floor(pl + chunk - 1 + bump)
    
    if ph > hi: ph = hi
       
    p = mp.Process(target=worker, args=(pl,ph,q))
    procs.append(p)

startTime = time.time() # get start time
for p in procs:
    p.start()           # start procs and wait for completion of queue

for p in procs:
    p.join()

primes = 0
for p in procs:
    primes += q.get()   # pickup and total stacked results

print( " %d        %0.4f" % (primes, (time.time() - startTime)))

