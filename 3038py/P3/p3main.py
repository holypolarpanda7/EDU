#!/usr/bin/env python3

import sys

import p3mod

gen = p3mod.find_starts()
gen.send(None)   # prime the generator

with open(sys.argv[1]) as f:
    for line in f:
        (seqid,seq) = line.strip().lower().split()
        startAndLocs = gen.send(seq)
        print(seqid, ' '.join( (str(sal) for sal in startAndLocs) ) )

gen.close()
