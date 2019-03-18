# Greg Wagner
# Python 3038 ~Dr. Butler
# p3mod.py module for Gene Sequencing -6/14/18

def find_starts():
    ss = []
    while True:
        line = yield ss # return ss (as manipulated below) and assigns sent (gen.send(sent) ) to line
        # print(line) # debug
        ss = []
        for i in range(len(line)):
            if line[i:i+3] == 'atg' or line[i:i+3] == 'gtg': 
                ss.append((line[i:i+3], i))
        # print('inside ', ss) # debug
