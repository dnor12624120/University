from Problem import Problem
import numpy as np

class Service():
    def __init__(self, runs, colony_size, iterations, size, alpha, beta, rho, q0, pheromone_amount, tau, default_trace):
        self.runs = runs
        self.colony_size = colony_size
        self.iterations = iterations
        self.size = size
        self.alpha = alpha
        self.beta = beta
        self.rho = rho
        self.q0 = q0
        self.pheromone_amount = pheromone_amount
        self.tau = tau
        self.default_trace = default_trace
        self.fitness_list = []

    def run(self):
        for i in range(1, self.runs + 1):
            print("Iteration #" + str(i) + ":")
            p = Problem(self.colony_size, self.iterations, self.size, self.alpha,
                self.beta, self.rho, self.q0, self.pheromone_amount, self.tau, self.default_trace)
            sol, f = p.run()
            self.fitness_list.append(f)
            print("Solution: \n" + str(sol))
            print("Fitness: " + str(f))
            print("Fitness mean: " + str(np.mean(self.fitness_list)))
            print("Fitness standard deviation: " + str(np.std(self.fitness_list)))

