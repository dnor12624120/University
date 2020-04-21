from random import uniform, choice
import numpy as np

from PermutationNetwork import PermutationNode, PermutationNetwork
from Utility import get_all, fitness

class Ant():
    def __init__(self, size, alpha, beta, q0, pheromone_amount, tau, network):
        self.size = size
        self.alpha = alpha
        self.beta = beta
        self.q0 = q0
        self.pheromone_amount = pheromone_amount
        self.tau = tau
        self.tour_length = 1
        self.network = network
        self.path = np.array([choice(get_all(size))])

    def get_random_choice(self):
        '''
            An ant will not revisit a previously visited node, so we can't reuse permutations.
            half denotes which half of permutations we're working with. We can have duplicates
            of permutations in the different halves of the matrix, so we need to keep track of that.
        '''
        half = 0 if len(self.path.tolist()) <= self.size else 1
        new_perm = choice(get_all(self.size))
        if half == 0: 
            first_half = self.path.tolist()[:self.size]
            while new_perm in first_half:
                new_perm = choice(get_all(self.size))
        else:
            second_half = self.path.tolist()[self.size:]
            while new_perm in second_half:
                new_perm = choice(get_all(self.size))
        return new_perm

    def get_next_moves(self):
        '''
            Valid nodes are nodes that have not been used yet, sorted by fitness
        '''
        n = len(self.path.tolist())
        if n <= self.size:
            valid_nodes = list(filter(lambda x: x not in self.path.tolist()[:self.size], get_all(self.size)))
        else:
            valid_nodes = list(filter(lambda x: x not in self.path.tolist()[self.size:], get_all(self.size)))
        sorted_nodes = []
        for node in valid_nodes:
            path_copy = self.path.tolist()[:]
            path_copy.append(node)
            sorted_nodes.append(np.array(path_copy))
        sorted_nodes = sorted(sorted_nodes, key=lambda node: fitness(self.size, node))
        return sorted_nodes

    def get_next_node(self):
        '''
            Returns node with best fitness to be selected
        '''
        moves = self.get_next_moves()
        node = choice(moves)
        trace_sum = 0
        val = 0

        # calculate trace sum
        for move in moves:
            f = fitness(self.size, move)
            trace_sum += self.get_edge_attractiveness(move[-1].tolist(), f)

        # find the most attractive node
        for move in moves:
            f = fitness(self.size, move)
            a = self.get_edge_attractiveness(move[-1].tolist(), f)
            if a / trace_sum > val:
                val = a / trace_sum
                node = move[-1].tolist()
        return node, val

    def get_edge_attractiveness(self, node, fitness):
        '''
            Edge attractiveness is determined by previous pheromone levels and distance 
            (in this case the fitness of the partial solution)
        '''
        current_node = self.path.tolist()[-1]
        tau = self.network.get_trace(current_node, node).trace
        # since our fitness function ranges from 0 to size * 2, we need to invert the original distance formula 
        eta = (1 / fitness)
        return (tau ** self.alpha) * (eta ** self.beta)

    def move(self):
        q = uniform(0, 1)
        if self.q0 < q: # node selected at random
            self.path = np.vstack((self.path, self.get_random_choice()))
        else: # most attractive node selected
            node, val = self.get_next_node()
            self.path = np.vstack((self.path, node))
            self.tour_length += val
        # add pheromone trace
        self.network.add_trace(self.path[-1].tolist(), self.path[-2].tolist(),
            (1 - self.tau) * self.network.get_trace(self.path[-1].tolist(), self.path[-2].tolist()).trace + self.tau * self.pheromone_amount)

    def reset(self, new_network):
        self.network = new_network
        self.path = np.array([choice(get_all(self.size))])
        self.tour_length = 1
        
