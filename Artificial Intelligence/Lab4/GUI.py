import sys
import os
import numpy

from PyQt5.Qt import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5 import uic

from WorkerThread import WorkerThread
from PLTWidget import PLTWidget
from Utility import fitness

class GUI(QMainWindow):
    def __init__(self):
        super(GUI, self).__init__()
        uic.loadUi('ui.ui', self)
        self.start_button.clicked.connect(self.start)
        self.stop_button.clicked.connect(self.stop)
        self.worker_thread = None
        self.fitness_list = []
        self.mean_list = []
        self.std_list = []
        self.pltwidget.canvas.draw()
        self.show()

    def init_textedits(self):
        self.solution.setEnabled(False)

    def start(self):
        self.fitness_list = []
        self.mean_list = []
        self.std_list = []
        try:
            self.finished.setText("")
            self.best.setText("Best fitness so far:")
            self.solution.setText("")
            particle_size = int(self.particle_edit.toPlainText())
            iterations = int(self.iterations_edit.toPlainText())
            swarm_size = int(self.swarm_edit.toPlainText())
            neighbourhoods = int(self.neighbourhood_edit.toPlainText())
            w = float(self.w_edit.toPlainText())
            c1 = float(self.c1_edit.toPlainText())
            c2 = float(self.c2_edit.toPlainText())
            self.thread = WorkerThread(30, iterations, swarm_size, neighbourhoods, particle_size, w, c1, c2)
            self.thread.run_finished.connect(self.update_graph)
            self.thread.start()
        except ValueError:
            pass
        
    def stop(self):
        self.thread.terminate()

    def update_graph(self, matrix):
        new_best = fitness(matrix.best)
        self.fitness_list.append(new_best)
        self.mean_list.append(numpy.average(self.fitness_list))
        self.std_list.append(numpy.std(self.fitness_list))
        self.pltwidget.canvas.axes.clear()
        self.pltwidget.canvas.axes.plot(self.fitness_list)
        self.pltwidget.canvas.axes.plot(self.mean_list)
        self.pltwidget.canvas.axes.plot(self.std_list)
        self.pltwidget.canvas.axes.legend(('Fitness', 'Mean', 'Standard Deviation'), loc='upper right')
        best = max(self.fitness_list)
        if(new_best >= best):
            self.solution.setText(str(matrix.best))
        self.best.setText("Best fitness so far: " + str(new_best))
        self.pltwidget.canvas.draw()
        if len(self.fitness_list) == 30:
            self.finished.setText("Finished!")