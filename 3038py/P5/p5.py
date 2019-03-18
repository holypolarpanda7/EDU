# Greg Wagner
# Python 3038 ~Dr. Butler
# p5.py 7/5/18
# Program accepts four cmd line args

import sys, hashlib

count = 0
name = sys.argv[1]
nSize = int(sys.argv[2])
zeros = int(sys.argv[3])
inString = sys.argv[4]

zs = []
for i in range(zeros):
    zs.append('0')
zeroStr = "".join(zs)

print('     ',inString)

for i in range(0,pow(10,nSize)): 
    h = hashlib.new(name)  # obj must be reconstructed to avoid continuous feed of data
    lead = []
    for x in range((nSize - len(str(i)))):
        lead.append('0')
    lead.append(str(i))
    toHash = "".join(lead) + inString
    h.update(toHash.encode())
    
    if (h.hexdigest())[0:zeros] == zeroStr:
        print('         ',"".join(lead), h.hexdigest())
        count += 1

print('     ',count)
