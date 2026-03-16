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

halucinated = False
multiple = False
with open("halucinated.txt", "w") as f: 
    for item in hs:
        if (hs[item] == 0):
            f.write("halucinated graph: " + item)
            halucinated = True
        if (hs[item] > 1):
            f.write("multiple graphs match same graph: " + item)
            multiple = True

if (some_missing):
    print("some graphs were not generated. see file missing_graphs.txt")

if (halucinated):
    print("some graphs were halucinated. see file halucinated.txt")

if (multiple):
    print("some graphs were generated multiple times. see file halucinated.txt")

print("finished")