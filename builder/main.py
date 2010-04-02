import sys

import PyQt4
from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *

import builder
from builder import BuilderWidget

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    builder = BuilderWidget()
    builder.setWindowOpacity(0.4)                                # transparence
    builder.setWindowFlags(QtCore.Qt.FramelessWindowHint)        # barre bleu
    builder.show()                                     # fullscreen
    app.exec_()                                             # main loop
