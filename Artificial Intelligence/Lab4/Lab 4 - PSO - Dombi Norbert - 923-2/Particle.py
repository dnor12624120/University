from random import uniform
from Utility import gen_perm, fitness, round_matrix

'''
    A particle is characterised by a permutation matrix, an inertia coefficient (w),
    a cognitive learning coefficient (c1) and a social learning coefficient (c2). These parameters
    will guide the particle's velocity and movement towards an optimised solution, along with
    its personal and neighbourhood best.
'''

class Particle():
    def __init__(self, size, w, c1, c2):
        self.size = size
        self.w = w
        self.c1 = c1
        self.c2 = c2
        self.position = gen_perm(self.size)
        self.velocity = gen_perm(self.size)
        self.best = self.position
        self.neighbourhood_best = None

    def get_position(self):
        return self.position
        
    def get_best(self):
        return self.best

    def get_neighbourhood_best(self):
        return self.neighbourhood_best

    def set_neighbourhood_best(self, neighbourhood_best):
        self.neighbourhood_best = neighbourhood_best

    def update(self):
        r1 = uniform(0, 1)
        r2 = uniform(0, 1)
        d1 = self.best - self.position
        d2 = self.neighbourhood_best - self.position
        new_velocity = (self.w * self.velocity) + (self.c1 * r1 * d1) + (self.c2 * r2 * d2)
        self.position = self.position + new_velocity
        self.velocity = new_velocity
        if fitness(self.position) > fitness(self.best):
            self.best = self.position
