from PyQt5.Qt import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from Solution import Solution
from Particle import Particle

class WorkerThread(QThread):
    run_finished = pyqtSignal(Particle)

    def __init__(self, solution_runs, iterations, swarm_size, num_neighbourhoods, particle_size, w, c1, c2):
        QThread.__init__(self)
        self.solution_runs = solution_runs
        self.iterations = iterations
        self.swarm_size = swarm_size
        self.num_neighbourhoods = num_neighbourhoods
        self.particle_size = particle_size
        self.w = w
        self.c1 = c1
        self.c2 = c2

    def run(self):
        for _ in range(self.solution_runs):
            sol = Solution(self.iterations, self.swarm_size, self.num_neighbourhoods, self.particle_size, self.w, self.c1, self.c2)
            particle = sol.run()
            self.run_finished.emit(particle)
