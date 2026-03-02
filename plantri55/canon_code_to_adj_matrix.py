#!/usr/bin/env python3
    
canon_code = list(map(int,input().split()))

nv = 0
for i in canon_code:
    if i == 0:
        nv += 1

index = 0
for i in range(nv):
    print(str(i + 1) + ".: ", end = "")
    while (canon_code[index] != 0):
        print(canon_code[index], end = " ")
        index += 1
    print(canon_code[index])
    index += 1

adj_matrix = []
for i in range(nv):
    adj_matrix.append([])
    for j in range(nv):
        adj_matrix[i].append(0)

adj_matrix[0][1] = 1
adj_matrix[1][0] = 1

index = 0
max_discovered = 1
for curr in range(nv):
    while canon_code[index] != 0:
        if (canon_code[index] > nv):
            max_discovered += 1
            adj_matrix[curr][max_discovered] = 1
            adj_matrix[max_discovered][curr] = 1
        else:
            adj_matrix[curr][canon_code[index] - 1] = 1
            adj_matrix[canon_code[index] - 1][curr] = 1
        
        index += 1
    index += 1

with open("adj_matrix.txt", "w") as f:
    for i in range(nv):
        f.write(" ".join(map(str, adj_matrix[i])) + "\n")