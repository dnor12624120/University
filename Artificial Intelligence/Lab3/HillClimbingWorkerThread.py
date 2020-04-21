from PyQt5.Qt import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from HillClimbingSolution import HillClimbingSolution
from Matrix import Matrix

class HillClimbingWorkerThread(QThread):
    run_finished = pyqtSignal(int, Matrix)

    def __init__(self, solution_runs, iterations, matrix_size):
        QThread.__init__(self)
        self.solution_runs = solution_runs
        self.iterations = iterations
        self.matrix_size = matrix_size

    def run(self):
        for _ in range(self.solution_runs):
            gs = HillClimbingSolution(self.iterations, self.matrix_size)
            best_fitness, matrix = gs.run()
            self.run_finished.emit(best_fitness, matrix)
