from Matrix import Matrix
from random import uniform

class Particle():
    def __init__(self, size, w, c1, c2):
        self.size = size
        self.w = w
        self.c1 = c1
        self.c2 = c2
        self.position = Matrix(self.size)
        self.velocity = Matrix(self.size)
        self.best = self.position
        self.swarm_best = None
        
    def get_best(self):
        return self.best

    def get_swarm_best(self):
        return self.swarm_best

    def set_swarm_best(self, swarm_best):
        self.swarm_best = swarm_best

    def get_position(self):
        return self.position

    def fitness(self):
        return self.position.fitness()

    def update(self):
        r1 = uniform(0, 1)
        r2 = uniform(0, 1)
        d1 = self.best - self.position
        d2 = self.swarm_best - self.position
        new_velocity = (self.w * self.velocity) + (self.c1 * r1 * d1) + (self.c2 * r2 * d2)
        self.position = self.position + new_velocity
        self.velocity = new_velocity
        if self.position.fitness() > self.best.fitness():
            self.best = self.position
