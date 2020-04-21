from PyQt5 import QtWidgets

from matplotlib.backends.backend_qt4agg import FigureCanvas
from matplotlib.figure import Figure

class PLTWidget(QtWidgets.QWidget):
    def __init__(self, parent = None):
        QtWidgets.QWidget.__init__(self, parent)
        self.canvas = FigureCanvas(Figure())
        layout = QtWidgets.QGridLayout()
        layout.addWidget(self.canvas)
        self.canvas.axes = self.canvas.figure.add_subplot(111)
        self.setLayout(layout)