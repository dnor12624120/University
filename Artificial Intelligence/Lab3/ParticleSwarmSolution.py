from Swarm import Swarm
from Particle import Particle

class ParticleSwarmSolution():
    def __init__(self, iterations, swarm_size, particle_size, w, c1, c2):
        self.iterations = iterations
        self.swarm = Swarm(swarm_size, particle_size, w, c1, c2)

    def run(self):
        solution = self.swarm.best()
        for _ in range(self.iterations):
            self.swarm.update()
            solution = self.swarm.best()
        return solution

pss = ParticleSwarmSolution(1000, 40, 4, 1, 0.1, 0.1)
s = pss.run()
print([str(x) for x in s.get_best().get_permutations()])
print(s.get_best().fitness())