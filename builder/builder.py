import PyQt4
from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *

class Box(QRect):
    def __init__(self, t_left=QPoint(), b_right=QPoint()):
        QRect.__init__(self, t_left, b_right)
        self.focus = 0

class BuilderWidget(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)

        self.focused = 0
        self.shiftPressed = 0
        self.leftButtonPressed = 0
        self.beginPos = QPoint()
        self.endPos = QPoint()
        self.list = []
        self.setGeometry(300, 300, 600, 600)
        self.setWindowTitle('IOT Builder')
        self.setMouseTracking(1)

    def selectBox(self, pos):
        topBox = 0
        for box in self.list:
            if box.normalized().contains(pos):
                topBox = box
            box.focus = 0
        self.focused = topBox
        if topBox:
            topBox.focus = 1

    def keyPressEvent(self, keyEvent):
        if self.focused:
            if keyEvent.key() == QtCore.Qt.Key_Left:
                self.focused.translate(-1, 0)
            elif keyEvent.key() == QtCore.Qt.Key_Right:
                self.focused.translate(1, 0)
            elif keyEvent.key() == QtCore.Qt.Key_Up:
                self.focused.translate(0, -1)
            elif keyEvent.key() == QtCore.Qt.Key_Down:
                self.focused.translate(0, 1)
            elif keyEvent.key() == QtCore.Qt.Key_Delete and self.focused != 0:
                self.list.remove(self.focused)
                self.focused = 0
            self.repaint()
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

    def onEdge(self, point, Box):
        if point.x() == Box.left():
            if point.y() >= Box.top() and point.y() <= Box.top() + 15:
                QtGui.QWidget.setCursor(self, Qt.SizeFDiagCursor)
            elif point.y() <= Box.bottom() and point.y() >= Box.bottom() - 15:
                QtGui.QWidget.setCursor(self, Qt.SizeBDiagCursor)
            else:
                QtGui.QWidget.setCursor(self, Qt.SizeHorCursor)
            return 1
        if point.x() == Box.right():
            if point.y() >= Box.top() and point.y() <= Box.top() + 15:
                QtGui.QWidget.setCursor(self, Qt.SizeBDiagCursor)
            elif point.y() <= Box.bottom() and point.y() >= Box.bottom() - 15:
                QtGui.QWidget.setCursor(self, Qt.SizeFDiagCursor)
            else:
                QtGui.QWidget.setCursor(self, Qt.SizeHorCursor)
            return 1

        if point.y() == Box.top():
            if point.x() >= Box.left() and point.x() <= Box.left() + 15:
                QtGui.QWidget.setCursor(self, Qt.SizeFDiagCursor)
            elif point.x() <= Box.right() and point.x() >= Box.right() - 15:
                QtGui.QWidget.setCursor(self, Qt.SizeBDiagCursor)
            else:
                QtGui.QWidget.setCursor(self, Qt.SizeHorCursor)
            return 1
        if point.y() == Box.bottom():
            if point.x() >= Box.left() and point.x() <= Box.left() + 15:
                QtGui.QWidget.setCursor(self, Qt.SizeBDiagCursor)
            elif point.x() <= Box.right() and point.x() >= Box.right() - 15:
                QtGui.QWidget.setCursor(self, Qt.SizeFDiagCursor)
            else:
                QtGui.QWidget.setCursor(self, Qt.SizeHorCursor)
            return 1
        return 0

    def mouseMoveEvent(self, mouseEvent):
        if self.leftButtonPressed:
            if self.focused != 0 and self.shiftPressed == 0 and self.leftButtonPressed == 1:   # deplacer la box
                self.focused.translate(mouseEvent.pos().x() - self.beginPos.x(), mouseEvent.pos().y() - self.beginPos.y())
                self.beginPos = QPoint(mouseEvent.pos())
            # if self.focused:
            #     self.focused.
            self.endPos = QPoint(mouseEvent.pos())
            self.repaint()
        else:
            for box in self.list:
                if self.onEdge(mouseEvent.pos(), box) == 1:
                    return
            QtGui.QWidget.setCursor(self, Qt.ArrowCursor)

    def mousePressEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 1
            self.beginPos = QPoint(mouseEvent.pos())
            if self.shiftPressed == 0:
                self.selectBox(mouseEvent.pos())
            self.repaint()
        else:
            QtGui.QWidget.mousePressEvent(self, mouseEvent)

    def mouseReleaseEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 0
            if self.shiftPressed == 1:
                self.endPos = mouseEvent.pos()
                va1 = QPoint(min(self.beginPos.x(), mouseEvent.pos().x()), min(self.beginPos.y(), mouseEvent.pos().y()))
                va2 = QPoint(max(self.beginPos.x(), mouseEvent.pos().x()), max(self.beginPos.y(), mouseEvent.pos().y()))
                self.list.append(Box(va1, va2))
                self.repaint()
        else:
            QtGui.QWidget.mouseReleaseEvent(self, mouseEvent)

    def paintEvent(self, event):
        paint = QtGui.QPainter()
        paint.begin(self)

        color = QtGui.QColor('#d4d4d4')
        colorFocus = QtGui.QColor('#aaaaaa')
        paint.setPen(color)

        paint.setBrush(QtGui.QColor(0, 0, 255, 80))              # RVB, opacity

        if self.leftButtonPressed and self.shiftPressed:
            paint.drawRect(self.beginPos.x(), self.beginPos.y(), self.endPos.x() - self.beginPos.x(), self.endPos.y() - self.beginPos.y())

        if self.list:
            for x in self.list:
                if x.focus == 1:
                    paint.setBrush(QtGui.QColor(0, 255, 0, 80))              # RVB, opacity
                    paint.drawRect(x)
                    paint.setBrush(QtGui.QColor(0, 0, 255, 80))              # RVB, opacity
                else:
                    paint.drawRect(x)
        paint.end()

