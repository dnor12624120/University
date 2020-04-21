from PyQt5.Qt import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from ParticleSwarmSolution import ParticleSwarmSolution
from Matrix import Matrix

class ParticleSwarmWorkerThread(QThread):
    run_finished = pyqtSignal(int, Matrix)

    def __init__(self, solution_runs, iterations, swarm_size, particle_size, w, c1, c2):
        QThread.__init__(self)
        self.solution_runs = solution_runs
        self.iterations = iterations
        self.swarm_size = swarm_size
        self.particle_size = particle_size
        self.w = w
        self.c1 = c1
        self.c2 = c2

    def run(self):
        print("START")
        for _ in range(self.solution_runs):
            gs = ParticleSwarmSolution(self.iterations, self.swarm_size, self.particle_size, self.w, self.c1, self.c2)
            best = gs.run()
            self.run_finished.emit(best.get_position().fitness(), best.get_position())

