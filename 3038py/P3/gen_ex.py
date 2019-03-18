# complex generator example to recive form sent and assign list

def gen():
    flag = False
    while True:
        if flag == False:
            line = (yield)
        print(line)
        ss = []
        for e in line:
            ss.append(e)
            if line.index(e) == -1:
                flag = False
            else:
                flag = True
        if flag == True:
            yield ss
        
