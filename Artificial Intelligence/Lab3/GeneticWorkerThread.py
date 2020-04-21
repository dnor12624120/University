from PyQt5.Qt import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from GeneticSolution import GeneticSolution
from Matrix import Matrix

class GeneticWorkerThread(QThread):
    run_finished = pyqtSignal(int, Matrix)

    def __init__(self, solution_runs, iterations, pop_size, matrix_size, mutation_rate, pop_cutoff):
        QThread.__init__(self)
        self.solution_runs = solution_runs
        self.iterations = iterations
        self.pop_size = pop_size
        self.matrix_size = matrix_size
        self.mutation_rate = mutation_rate
        self.pop_cutoff = pop_cutoff

    def run(self):
        for _ in range(self.solution_runs):
            gs = GeneticSolution(self.iterations, self.pop_size, self.matrix_size, self.mutation_rate, self.pop_cutoff)
            best_fitness, matrix = gs.run()
            self.run_finished.emit(best_fitness, matrix)
