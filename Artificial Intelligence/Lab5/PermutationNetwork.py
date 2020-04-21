from Utility import get_all
import itertools

class PermutationNode():
    def __init__(self, edge1, edge2, trace):
        self.edge1 = edge1
        self.edge2 = edge2
        self.trace = trace

    def __str__(self):
        return "(" + str(self.edge1) + ", " + str(self.edge2) + ") : " + str(self.trace)

class PermutationNetwork():
    def __init__(self, size, default_trace):
        self.size = size
        self.default_trace = default_trace
        self.nodes = []
        self.init_edges()

    def init_edges(self):
        for pair1, pair2 in itertools.product(get_all(self.size), repeat=2):
            if pair1 != pair2:
                self.nodes.append(PermutationNode(pair1, pair2, self.default_trace))
                self.nodes.append(PermutationNode(pair2, pair1, self.default_trace))

    def get_node_index(self, i, j):
        index = None
        for k in range(len(self.nodes)):
            if self.nodes[k].edge1 == i and self.nodes[k].edge2 == j:
                  index = k
                  break
        return index

    def add_trace(self, i, j, trace_amount):
        self.nodes[self.get_node_index(i, j)].trace += trace_amount

    def get_trace(self, i, j):
        return self.nodes[self.get_node_index(i, j)]
