from Permutation import Permutation
from Utility import next_permutation

import itertools
import math
import random

class Matrix():
    def __init__(self, size):
        self.size = size
        self.permutations = self.generate_permutation_pool()

    def set_permutations(self, permutations):
        self.size = int(len(permutations) / 2)
        self.permutations = permutations

    def get_all_permutations(self):
        # Returns a list of all n! permutations (as lists) of an integer n (n being the size of the matrix)
        return list(list(x) for x in itertools.permutations(list(range(1, self.size + 1))))

    def generate_n_permutations(self):
        # Randomly selects n unique permutations and returns them as a list
        all_permutations = self.get_all_permutations()
        selected_permutations = [] 
        for _ in range(self.size):
            permutation = random.choice(all_permutations)
            selected_permutations.append(permutation)
            all_permutations.remove(permutation)
        return selected_permutations

    def generate_permutation_pool(self):
        # generates the 2 permutation sets that make up the matrix
        permutations1 = [Permutation(perm) for perm in self.generate_n_permutations()]
        permutations2 = [Permutation(perm) for perm in self.generate_n_permutations()]
        return permutations1 + permutations2

    def mutate(self):
        # By mutating a permutation at a random position gets replaced by another random permutation
        i = random.randint(0, self.size * 2 - 1)
        j = random.randint(0, self.size * 2 - 1)
        x = list(list(itertools.permutations(list(range(1, self.size + 1))))[j])
        self.permutations[i] = Permutation(x)
            
    def fitness(self):
        f = 0 
        pool1 = self.permutations[:self.size] # first set of permutations
        pool2 = self.permutations[self.size:] # second set of permutations

        for i in range(self.size):
            if any(pool1[i].get_symbols()) > self.size:
                print("!")
                return 0
            if any(pool2[i].get_symbols()) > self.size:
                print("!")
                return 0

        # check that all columns form permutations
        for i in range(self.size):
            perm = []
            for c in pool1:
                sym = c.get_symbols()
                perm.append(sym[i])
            if len(perm) == len(set(perm)):
                f += 1
            perm = []
            for c in pool2:
                sym = c.get_symbols()
                perm.append(sym[i])
            if len(perm) == len(set(perm)):
                f += 1
        # check that no row-wise pairs are identical
        for i in range(self.size):
            sym1 = pool1[i].get_symbols()
            sym2 = pool2[i].get_symbols()
            if len(list(zip(sym1, sym2))) != len(set(list(zip(sym1, sym2)))):
                f -= 1
        return f

    def get_neighbours(self):
        perms = [p.get_symbols() for p in self.permutations]
        # neighbours are obtained by shuffling each permutation, one by one, once
        # resulting in 2 * n neighbours
        for i in range(self.size * 2):
            copy = perms[:]
            copy[i] = next_permutation(copy[i])
            m = Matrix(self.size)
            m.set_permutations([Permutation(x) for x in copy])
            yield m

    def get_size(self):
        return self.size

    def get_permutations(self):
        return self.permutations

    def __mul__(self, i):
        m = Matrix(self.size)
        m.set_permutations([x * i for x in self.permutations])
        return m

    def __rmul__(self, i):
        m = Matrix(self.size)
        m.set_permutations([x * i for x in self.permutations])
        return m

    def __add__(self, other):
        m = Matrix(self.size)
        m.set_permutations([x[0] + x[1] for x in list(zip(self.permutations, other.permutations))])
        return m

    def __sub__(self, other):
        m = Matrix(self.size)
        m.set_permutations([x[0] - x[1] for x in list(zip(self.permutations, other.permutations))])
        return m

    def __str__(self):
        return str([str(c) for c in self.permutations])

