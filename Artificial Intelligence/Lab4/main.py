import sys
from GUI import GUI
from PyQt5 import QtWidgets, uic

app = QtWidgets.QApplication(sys.argv)
gui = GUI()
app.exec_()