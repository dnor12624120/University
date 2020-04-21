from itertools import permutations

def next_permutation(perm):
    # returns the next lexicographic neighbour of a given permutation
    all = list(list(x) for x in permutations(list(range(1, len(perm) + 1))))
    return all[(all.index(perm) + 1) % len(all)]
    