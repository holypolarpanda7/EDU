
import time
import multiprocessing as mp

def worker_bee(a, b, q):
    s = 0
    for n in range(a, b):
        s += n
    print(mp.current_process().name, a, b-1, s)
    q.put(s)

print("cpu_count: ",mp.cpu_count())  ## just for demo

procs = []
q = mp.Queue()
n = 4

big_number = 16
chunk = int(big_number / n)
for i in range(n):
    lo = i * chunk+1
    hi = (i+1) * chunk+1
    p = mp.Process(target=worker_bee, args=(lo,hi,q))
    procs.append(p)

startTime = time.time()
for p in procs:
    p.start()

for p in procs:
    p.join()

print( "%0.4f" % (time.time() - startTime) )

s = 0
for p in procs:
    s += q.get()

print('total', s)

