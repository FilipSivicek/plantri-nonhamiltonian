narboni = open("incorrect.txt", "r")

hs = dict()
for line in narboni:
    hs[line] = 0

no_ladder = open("correct.txt", "r")

number = 1
for line in no_ladder:
    if line not in hs:
        print("missing graph " + str(number) + ": " + line)
    else:
        hs[line] += 1
    
    number += 1

for item in hs:
    print(hs[item], end = " ")

print("finished")