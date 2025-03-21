# This program check if no_symetry.c works correctly.
# It does so by getting set S1 of all graph of given size,
# set S2 of all graphs with automorphisms , set S3 of
# all graphs without automorphisms and checking If
# S1 = S2 U S3

name1 = input("Insert whole set filename: ")
file1 = open(name1) #whole set

whole_set = set()

for line in file1:
    whole_set.add(line)
print(len(whole_set))

name2 = input("Insert with automorphism set filename: ")
file2 = open(name2)

other_set = set()

for line in file2:
    other_set.add(line)
print(len(other_set))

name3 = input("Insert without automorphism set filename: ")
file3 = open(name3)

for line in file3:
    other_set.add(line)
print(len(other_set))

print(other_set == whole_set)
