from Population import Population
from Matrix import Matrix
import random
from math import ceil

class GeneticSolution():
    def __init__(self, iterations, pop_size, matrix_size, mutation_rate, pop_cutoff):
        self.target_fitness = matrix_size * 2
        self.iterations = iterations
        self.mutation_rate = mutation_rate
        self.pop_cutoff = pop_cutoff
        self.matrix_size = matrix_size
        self.pop_size = pop_size
        self.pop = Population(pop_size, matrix_size)

    def run(self):
        best_fitness = 0
        best_solution = None
        for _ in range(self.iterations):
            if self.target_fitness in self.pop.get_fitness_for_all():
                break

            matrices = self.pop.get_matrices()
            matrices = self.selection(matrices)
            matrices = self.crossover(matrices)
            matrices = self.mutate(matrices)

            self.pop.set_matrices(matrices)

            pairs = list(zip(self.pop.get_fitness_for_all(), self.pop.get_matrices()))
            pairs = sorted(pairs, key=lambda pair: pair[0], reverse=True)
            if pairs[0][0] > best_fitness:
                best_fitness = pairs[0][0]
                best_solution = pairs[0][1]
        return best_fitness, best_solution


    def selection(self, matrices):
        # Sort matrices by fitness and only keep the top 'pop_cutoff' percent
        matrices = sorted(matrices, key=lambda m: m.fitness(), reverse=True)
        matrices = matrices[:int(self.pop_cutoff * len(matrices))]
        return matrices

    def crossover(self, matrices):
        offspring = []
        # we need to generate 'self.pop_size - len(matrices)' offspring in order to get up to our original population
        for _ in range((self.pop_size - len(matrices)) // 2):
            # generate 2 distinct indices for parents
            i = random.randint(0, len(matrices) - 1)
            j = random.randint(0, len(matrices) - 1)
            while i == j:
                i = random.randint(0, len(matrices) - 1)
                j = random.randint(0, len(matrices) - 1)
            parent1_perm = matrices[i].get_permutations()
            parent2_perm = matrices[j].get_permutations()
            # the childs permutations will be made up of chunks of its parents' permutations
            # permutations [0:n1], [n2:n] will be from parent1
            # permutations [n1:n2] will be from parent2
            n1 = random.randint(1, self.matrix_size - 1)
            n2 = (self.matrix_size * 2)  - n1
            child_permutations1 = parent1_perm[:n1] + parent2_perm[n1:n2] + parent1_perm[n2:]
            child_permutations2 = parent2_perm[:n1] + parent1_perm[n1:n2] + parent2_perm[n2:]
            child1 = Matrix(1)
            child2 = Matrix(1)
            child1.set_permutations(child_permutations1)
            child2.set_permutations(child_permutations2)
            # add child to offspring list
            offspring.append(child1)
            offspring.append(child2)
        # append offspring to population
        return matrices + offspring

    def mutate(self, matrices):
        if random.uniform(0, 1) <= self.mutation_rate:
            i = random.randint(0, len(matrices) - 1)
            matrices[i].mutate()
        return matrices
