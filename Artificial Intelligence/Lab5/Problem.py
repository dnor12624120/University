from PermutationNetwork import PermutationNetwork
from Ant import Ant
from Utility import fitness

class Problem():
    def __init__(self, colony_size, iterations, size, alpha, beta, rho, q0, pheromone_amount, tau, default_trace):
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
        self.colony = [Ant(size, alpha, beta, q0, pheromone_amount, tau, PermutationNetwork(size, default_trace)) for _ in range(colony_size)]

    def get_old_network(self):
        '''
            The old network is the sum of all personal networks of ants
        '''
        network = PermutationNetwork(self.size, 0)
        for ant in self.colony:
            for node in ant.network.nodes:
                network.add_trace(node.edge1, node.edge2, node.trace)
        return network

    def get_updated_network(self):
        old_network = self.get_old_network()
        network = PermutationNetwork(self.size, 0) # create a blank network
        for ant in self.colony:
            for i in range(self.size * 2 - 1):
                trace = ant.network.get_trace(ant.path[i].tolist(), ant.path[i + 1].tolist()).trace # get trace of edge
                trace /= ant.tour_length # divide it by tour length
                network.add_trace(ant.path[i].tolist(), ant.path[i + 1].tolist(), trace)
        for node in network.nodes:
            node.trace += (1 - self.rho) * old_network.get_trace(node.edge1, node.edge2).trace
        return network

    def get_best_path(self):
        paths = [ant.path for ant in self.colony]
        return max(paths, key=lambda path: fitness(self.size, path))

    def run(self):
        best_fitness = 0
        best_solution = None
        for i in range(1, self.iterations + 1):
            for ant in self.colony:
                ant.move()
            if i % (self.size * 2 - 1) == 0: # ants have completed their tours at this point
                solution = self.get_best_path()
                if fitness(self.size, solution) > best_fitness:
                    best_solution = solution
                    best_fitness = fitness(self.size, solution)
                if fitness(self.size, best_solution) == self.size * 2:
                    break
                updated_network = self.get_updated_network()
                for ant in self.colony:
                    ant.reset(updated_network)
        return best_solution, best_fitness


        
                


