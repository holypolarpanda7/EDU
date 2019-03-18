# Greg Wagner
# Python 3038 ~Dr. Butler
# Dart Problem -6/7/18
#!/usr/bin/env python3

import sys, random, math

# Argument N from system argument
n = int(sys.argv[1])

# count = number of hits in circle
count = 0

for i in range(n):
    x = random.random()
    y = random.random()
    if  math.sqrt(x*x + y*y) <= 1:
        count += 1 

print ('pi estimate =', (count/n*4))
