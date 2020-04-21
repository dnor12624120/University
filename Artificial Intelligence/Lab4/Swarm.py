from Particle import Particle
from Utility import fitness

'''
    The class represents a collction of 'size' particles of size 'particle_size',
    having their coefficients given by w, c1, c2. Neighbourhoods are created
    in linear fashion, making sure that no particle remains isolated.
'''

class Swarm():
    def __init__(self, size, num_neighbourhoods, particle_size, w, c1, c2):
        self.size = size
        self.particle_size = particle_size
        self.swarm = [Particle(particle_size, w, c1, c2) for _ in range(self.size)]
        self.num_neighbourhoods = num_neighbourhoods

    def get_neighbourhood(self, neighbourhood_index):
        x1 = neighbourhood_index * (self.size // self.num_neighbourhoods)
        x2 = (neighbourhood_index + 1) * (self.size // self.num_neighbourhoods)
        return self.swarm[x1:x2]

    def neighbourhood_best(self, neighbourhood_index):
        return max(self.get_neighbourhood(neighbourhood_index), key=lambda p: fitness(p.best))

    def swarm_best(self):
        return max(self.swarm, key=lambda p: fitness(p.best))

    def update(self):
        for neighbourhood_index in range(self.num_neighbourhoods):
            # get the best of each neighbourhood
            neighbourhood_best = self.neighbourhood_best(neighbourhood_index)
            # set it for all other particles
            for p in self.get_neighbourhood(neighbourhood_index):
                p.set_neighbourhood_best(neighbourhood_best.best)
        # update them
        for p in self.swarm:
            p.update()

