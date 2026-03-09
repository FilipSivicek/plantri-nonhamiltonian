#!/usr/bin/env python3

narboni = open("incorrect.txt", "r")

hs = dict()
for line in narboni:
    if (line in hs):
        print("same graph generated multiple times: ", end = "")
        print(line)
    hs[line] = 0

no_ladder = open("correct.txt", "r")


number = 1
some_missing = False
with open("missing_graphs.txt", "w") as f:
    for line in no_ladder:
        if line not in hs:
            f.write("missing graph " + str(number) + ": " + line + "\n")
            some_missing = True
        else:
            hs[line] += 1

        number += 1

for item in hs:
    if (hs[item] == 0):
        print("halucinated graph: " + item)
    if (hs[item] > 1):
        print("multiple graphs match same graph: " + item)

if (some_missing):
    print("some graphs were not generated. see file missing_graphs.txt")
print("finished")