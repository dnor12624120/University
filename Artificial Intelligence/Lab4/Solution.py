from Swarm import Swarm
from Utility import round_matrix

class Solution():
    def __init__(self, iterations, swarm_size, num_neighbourhoods, particle_size, w, c1, c2):
        self.iterations = iterations
        self.swarm_size = swarm_size
        self.num_neighbourhoods = num_neighbourhoods
        self.particle_size = particle_size
        self.w = w
        self.c1 = c1
        self.c2 = c2

    def run(self):
        s = Swarm(self.swarm_size, self.num_neighbourhoods, self.particle_size, self.w, self.c1, self.c2)
        best = None
        for _ in range(self.iterations):
            s.update()
            best = s.swarm_best()
        return best


