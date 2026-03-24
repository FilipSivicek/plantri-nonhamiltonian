#!/usr/bin/env python3

narboni = open("output_verifier/canon_codes_my_gen.txt", "r")

hs = dict()

multiple = False
with open("output_verifier/multiple.txt", "w") as f:
    for line in narboni:
        if (line in hs):
            f.write("same graph generated multiple times: " + line + "\n")
            multiple = True
        hs[line] = 0

no_ladder = open("output_verifier/output_plantri.txt", "r")

number = 1
some_missing = False
with open("output_verifier/missing_graphs.txt", "w") as f:
    for line in no_ladder:
        if line not in hs:
            f.write("missing graph " + str(number) + ": " + line + "\n")
            some_missing = True
        else:
            hs[line] += 1

        number += 1

halucinated = False
with open("output_verifier/halucinated.txt", "w") as f: 
    for item in hs:
        if (hs[item] == 0):
            f.write("halucinated graph: " + item + "\n")
            halucinated = True

if (some_missing):
    print("some graphs were not generated. see file output_verifier/missing_graphs.txt")

if (halucinated):
    print("some graphs were halucinated. see file output_verifier/halucinated.txt")

if (multiple):
    print("some graphs were generated multiple times. see file output_verifier/halucinated.txt")

print("finished")