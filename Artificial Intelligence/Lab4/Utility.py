import numpy as np
import itertools
from random import choice

def get_all(n):
    return list(list(x) for x in itertools.permutations(list(range(1, n + 1))))

def gen_perm(n):
    all_permutations = get_all(n)
    selected_permutations = [] 
    for _ in range(2 * n):
        permutation = choice(all_permutations)
        selected_permutations.append(permutation)
        all_permutations.remove(permutation)
    return np.array(selected_permutations)

def round_matrix(matrix):
    copy = []
    for i in range(len(matrix)):
        copy.append([round(x) for x in matrix.tolist()[i]])
    return np.array(copy)

def fitness(matrix):
    f = 0 
    size = len(matrix) // 2
    copy = round_matrix(matrix)
    pool1 = copy.tolist()[:size] # first set of permutations
    pool2 = copy.tolist()[size:] # second set of permutations
                
    # check that all columns form permutations
    for i in range(size):
        col = []
        for perm in pool1:
            if perm[i] > size:
                return 0
            col.append(perm[i])
        if len(col) == len(set(col)):
            f += 1
        col = []
        for perm in pool2:
            if perm[i] > size:
                return 0
            col.append(perm[i])
        if len(col) == len(set(col)):
            f += 1
        # check that no row-wise pairs are identical
    for i in range(size):
        perm1 = pool1[i]
        perm2 = pool2[i]
        if len(list(zip(perm1, perm2))) != len(set(list(zip(perm1, perm2)))):
            f -= 1
    return f

