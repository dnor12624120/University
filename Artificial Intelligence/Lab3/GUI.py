import sys
import os
import numpy

from PyQt5.Qt import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5 import uic

from GeneticWorkerThread import GeneticWorkerThread
from HillClimbingWorkerThread import HillClimbingWorkerThread
from ParticleSwarmWorkerThread import ParticleSwarmWorkerThread
from PLTWidget import PLTWidget

class GUI(QMainWindow):

    def __init__(self, width, height, title):
        super(GUI, self).__init__()
        uic.loadUi('ui.ui', self)
        self.start_button.clicked.connect(self.start)
        self.stop_button.clicked.connect(self.stop)
        self.start_button2.clicked.connect(self.start)
        self.stop_button2.clicked.connect(self.stop)
        self.start_button3.clicked.connect(self.start)
        self.stop_button3.clicked.connect(self.stop)
        self.genetic_thread = None
        self.hillclimbing_thread = None
        self.particleswarm_thread = None
        self.fitness_list = []
        self.mean_list = []
        self.std_list = []
        self.init_textedits()
        self.pltwidget.canvas.draw()
        self.show()

    def init_textedits(self):
        self.solution.setEnabled(False)
        self.solution2.setEnabled(False)
        self.matrix_edit.setText("4")
        self.iterations_edit.setText("1000")
        self.popsize_edit.setText("40")
        self.mutation_edit.setText("0.2")
        self.cutoff_edit.setText("0.8")
        self.matrix_edit2.setText("4")
        self.iterations_edit2.setText("1000")
        self.matrix_edit3.setText("4")
        self.iterations_edit3.setText("1000")
        self.popsize_edit3.setText("40")
        self.w_edit.setText("0.2")
        self.c1_edit.setText("0.3")
        self.c2_edit.setText("0.5")

    def start(self):
        self.fitness_list = []
        self.mean_list = []
        self.std_list = []
                
        if self.tabWidget.currentIndex() == 0:
            try:
                self.finished.setText("")
                self.best.setText("Best fitness so far:")
                self.solution.setText("")
                matrix_size = int(self.matrix_edit.toPlainText())
                iterations = int(self.iterations_edit.toPlainText())
                popsize = int(self.popsize_edit.toPlainText())
                mutation = float(self.mutation_edit.toPlainText())
                cutoff = float(self.cutoff_edit.toPlainText())
                self.genetic_thread = GeneticWorkerThread(30, iterations, popsize, matrix_size, mutation, cutoff)
                self.genetic_thread.run_finished.connect(self.update_graph1)
                self.genetic_thread.start()
            except ValueError:
                pass
        elif self.tabWidget.currentIndex() == 1:
            try:
                self.finished2.setText("")
                self.best2.setText("Best fitness so far:")
                self.solution2.setText("")
                matrix_size = int(self.matrix_edit2.toPlainText())
                iterations = int(self.iterations_edit2.toPlainText())
                self.hillclimbing_thread = HillClimbingWorkerThread(30, iterations, matrix_size)
                self.hillclimbing_thread.run_finished.connect(self.update_graph2)
                self.hillclimbing_thread.start()
            except ValueError:
                pass
        elif self.tabWidget.currentIndex() == 2:
            try:
                self.finished3.setText("")
                self.best3.setText("Best fitness so far:")
                self.solution3.setText("")
                matrix_size = int(self.matrix_edit3.toPlainText())
                iterations = int(self.iterations_edit3.toPlainText())
                popsize = int(self.popsize_edit3.toPlainText())
                w = float(self.w_edit.toPlainText())
                c1 = float(self.c1_edit.toPlainText())
                c2 = float(self.c2_edit.toPlainText())
                self.particleswarm_thread = ParticleSwarmWorkerThread(30, iterations, popsize, matrix_size, w, c1, c2)
                self.particleswarm_thread.run_finished.connect(self.update_graph3)
                self.particleswarm_thread.start()
            except ValueError:
                pass

    def stop(self):
        if self.tabWidget.currentIndex() == 0:
            self.genetic_thread.terminate()
        elif self.tabWidget.currentIndex() == 1:
            self.hillclimbing_thread.terminate()
        elif self.tabWidget.currentIndex() == 2:
            self.particleswarm_thread.terminate()

    def update_graph1(self, new_best, matrix):
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
            self.solution.setText(str([str(x) for x in matrix.get_permutations()]))
        self.best.setText("Best fitness so far: " + str(best))
        self.pltwidget.canvas.draw()
        if len(self.fitness_list) == 30:
            self.finished.setText("Finished!")

    def update_graph2(self, new_best, matrix):
        self.fitness_list.append(new_best)
        self.mean_list.append(numpy.average(self.fitness_list))
        self.std_list.append(numpy.std(self.fitness_list))
        self.pltwidget2.canvas.axes.clear()
        self.pltwidget2.canvas.axes.plot(self.fitness_list)
        self.pltwidget2.canvas.axes.plot(self.mean_list)
        self.pltwidget2.canvas.axes.plot(self.std_list)
        self.pltwidget2.canvas.axes.legend(('Fitness', 'Mean', 'Standard Deviation'), loc='upper right')
        best = max(self.fitness_list)
        if(new_best >= best):
            self.solution2.setText(str([str(x) for x in matrix.get_permutations()]))
        self.best2.setText("Best fitness so far: " + str(best))
        self.pltwidget2.canvas.draw()
        if len(self.fitness_list) == 30:
            self.finished2.setText("Finished!")

    def update_graph3(self, new_best, matrix):
        self.fitness_list.append(new_best)
        self.mean_list.append(numpy.average(self.fitness_list))
        self.std_list.append(numpy.std(self.fitness_list))
        self.pltwidget3.canvas.axes.clear()
        self.pltwidget3.canvas.axes.plot(self.fitness_list)
        self.pltwidget3.canvas.axes.plot(self.mean_list)
        self.pltwidget3.canvas.axes.plot(self.std_list)
        self.pltwidget3.canvas.axes.legend(('Fitness', 'Mean', 'Standard Deviation'), loc='upper right')
        best = max(self.fitness_list)
        if(new_best >= best):
            self.solution3.setText(str([str(x) for x in matrix.get_permutations()]))
        self.best3.setText("Best fitness so far: " + str(best))
        self.pltwidget3.canvas.draw()
        if len(self.fitness_list) == 30:
            self.finished3.setText("Finished!")

