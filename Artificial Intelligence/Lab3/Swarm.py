from Particle import Particle

class Swarm():
    def __init__(self, size, particle_size, w, c1, c2):
        self.size = size
        self.particle_size = particle_size
        self.swarm = [Particle(particle_size, w, c1, c2) for _ in range(self.size)]

    def best(self):
        return max(self.swarm, key=lambda p: p.get_best().fitness())

    def update(self):
        # calculate swarm best
        swarm_best = self.best()
        # set it for all particles
        for p in self.swarm:
            p.set_swarm_best(swarm_best.get_position())
        # update them
        for p in self.swarm:
            p.update()
