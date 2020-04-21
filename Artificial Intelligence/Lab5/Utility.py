import numpy as np
import itertools
from random import choice

def random_permutation(n):
    return choice(get_all(n))

def get_all(n):
    return list(list(x) for x in itertools.permutations(list(range(1, n + 1))))

def fitness(size, state):
    '''
        The function receives a potentially incomplete state (NxN matrix of double permutations)
        that it has to create a score for. 
    '''
    f = 0
    n = len(state) # actual size
    first_half = state.tolist()[:size]
    second_half = state.tolist()[size:]
    for i in range(size):
        col = []
        for perm in first_half:
            col.append(perm[i])
        if len(col) == len(set(col)):
            f += 1
        col = []
        if n > size:
            for perm in second_half:
                col.append(perm[i])
            if len(col) == len(set(col)):
                f += 1
    return 0.00001 if f == 0 else f

