import PyQt4
from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *

class BuilderWidget(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)

        self.shiftPressed = 0
        self.leftButtonPressed = 0
        self.beginPos = QPoint()
        self.endPos = QPoint()
        self.list = []
        self.setGeometry(300, 300, 600, 600)
        self.setWindowTitle('IOT Builder')

    def selectRegion(self, pos):
        for region in self.list:
            if region.contains(pos):
                print "lolz"

    def keyPressEvent(self, keyEvent):
        if keyEvent.key() == QtCore.Qt.Key_Shift:
            self.shiftPressed = 1
        elif keyEvent.key() == QtCore.Qt.Key_Escape:
            self.close()
        else:
            QtGui.QWidget.keyPressEvent(self, keyEvent)

    def keyReleaseEvent(self, keyEvent):
        if keyEvent.key() == QtCore.Qt.Key_Shift:
            self.shiftPressed = 0
            self.repaint()
        else:
            QtGui.QWidget.keyReleaseEvent(self, keyEvent)

    def mouseMoveEvent(self, mouseEvent):
        if self.leftButtonPressed:
            self.endPos = QPoint(mouseEvent.pos())
            self.repaint()
        else:
            QtGui.QWidget.mouseMoveEvent(self, mouseEvent)

    def mousePressEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 1
            self.beginPos = QPoint(mouseEvent.pos())
            if self.shiftPressed == 0:
                self.selectRegion(mouseEvent.pos())
        else:
            QtGui.QWidget.mousePressEvent(self, mouseEvent)

    def mouseReleaseEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 0
            if self.shiftPressed == 1:
                self.endPos = mouseEvent.pos()
                self.list.append(QRect(self.beginPos, mouseEvent.pos()))
                self.repaint()
        else:
            QtGui.QWidget.mouseReleaseEvent(self, mouseEvent)

    def paintEvent(self, event):
        paint = QtGui.QPainter()
        paint.begin(self)

        color = QtGui.QColor(0, 0, 0)
        color.setNamedColor('#d4d4d4')
        paint.setPen(color)

        paint.setBrush(QtGui.QColor(0, 0, 255, 80))              # RVB, opacity

        if self.leftButtonPressed and self.shiftPressed:
            paint.drawRect(self.beginPos.x(), self.beginPos.y(), self.endPos.x() - self.beginPos.x(), self.endPos.y() - self.beginPos.y())
        if self.list:
            for x in self.list:
                paint.drawRect(x)
        paint.end()
