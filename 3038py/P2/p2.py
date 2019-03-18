# Greg Wagner
# Python 3038 ~Dr. Butler
# Gene Sequencing -6/14/18
#!/usr/bin/env python3

import sys

filename = sys.argv[1]
myIn = open(filename)

line = myIn.readline()
while line:
    start = None
    splLine = line.split()
    id = splLine[0]
    seq = splLine[1]
    
    for i in range(len(seq)):

        if seq[i:i+3].lower() == 'atg' or seq[i:i+3].lower() == 'gtg':
            start = i
            fCodon = seq[i:i+3]
            endFlag = False
            for k in range(len(seq[i:len(seq)])):
                
                if endFlag == False and seq[i+k:i+k+3].lower() == 'tag':
                    stop = i+k+3
                    endFlag = True
                    lCodon = seq[i+k:i+k+3]
                    if (k + 3) >= 33 and (k + 3) <= 66:
                        print(id, format(start,"3d"), format((stop-start),"3d"), fCodon, lCodon)
            
    line = myIn.readline()
myIn.close()

