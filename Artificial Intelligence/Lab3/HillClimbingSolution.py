from Population import Population
from Matrix import Matrix
import random
from math import ceil

class HillClimbingSolution():
    def __init__(self, iterations, matrix_size):
        self.target_fitness = matrix_size * 2
        self.iterations = iterations
        self.matrix_size = matrix_size
        
    def run(self):
        matrix = Matrix(self.matrix_size)
        fitness = matrix.fitness()

        for _ in range(self.iterations):
            improved = False
            for neighbour in matrix.get_neighbours():
                # look for neighbour with highest fitness
                if neighbour.fitness() > fitness:
                    fitness = neighbour.fitness()
                    matrix = neighbour
                    improved = True

            if fitness == self.target_fitness:
                # we can stop if we found a solution
                break
            
            if not improved:
                # if we've not reached the target fitness and we haven't improved from the previous iteration,
                # it means we've reached a local maximuma and need to restart
                matrix = Matrix(self.matrix_size)

        return fitness, matrix