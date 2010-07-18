# IOT Copyright (C) 2010 Builder development team
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2
# as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
# Authors: Builder <builder@ionlythink.com>, http://www.ionlythink.com

import sys

import PyQt4
from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *
from PyQt4.QtGui import *

import box, toolbar
from box import Box
from toolbar import Toolbar

import xml.parsers.expat, sys

class Mode:
    box = 0
    selection = 1

class Action:
    zoom = 0
    clickLeft = 1
    clickDouble = 2
    clickRight = 3

class BuilderWidget(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)

        try:
            self.toolbar = Toolbar(self)
            self.addToolBar(self.toolbar)
        except:
            print "Unexpected error:", sys.exc_info()[0]
            raise

        self.init()
        self.setGeometry(300, 300, 600, 600)
        self.setWindowTitle('IOT Builder')
        self.setMouseTracking(1)
        self.saveDialog = 'Save xml file'
        self.loadDialog = 'Open xml file'
        self.extensionDialog = 'Xml Files (*.xml)'
        self.extension = '.xml'

    def init(self):
        self.tolerance = 0
        self.curs = 0
        self.focused = None
        self.clipboard = None
        self.father = None
        self.mode = Mode.selection
        self.leftButtonPressed = 0
        self.beginPos = QPoint()
        self.endPos = QPoint()
        self.list = []

    def newFile(self):
        if self.list or self.father:
            r = QMessageBox.question(self, 'IotBuilder', \
                                     'Are you sure to clean all boxes ?', \
                                     QMessageBox.Ok, QMessageBox.Cancel)
            if r == QMessageBox.Cancel:
                return
        self.init()
        self.repaint()

    def saveFile(self):
        filename = QFileDialog.getSaveFileName(None, \
                                               self.saveDialog, \
                                               QDir.currentPath(), \
                                               self.extensionDialog)
        if filename == '':
            return
        if not QString(filename).endsWith(self.extension):
            filename.append(self.extension)
        if QDir(QDir.currentPath()).exists(filename):
            QMessageBox.critical(self, 'IotBuilder', 'File already exists...')
            return

        qfile = QFile(filename)
        if qfile.open(QIODevice.WriteOnly | QIODevice.Text):
            out = QTextStream(qfile)
            out << '<boxes id="NomProgram">' + "\n"
            while self.list[0].father:
                self.zoomOut()
            out << self.xmlRec(self.list)
            out << '</boxes>' + "\n"
            qfile.close()

    def xmlRec(self, li):
        tmp = ''
        for elem in li:
            tmp += '<box type="1" x="' + str(elem.topLeft().x()) + '" y="' + str(elem.topLeft().y()) + '" width="' + str(elem.bottomRight().x() - elem.topLeft().x()) + '" height="' + str(elem.bottomRight().y() - elem.topLeft().y()) + '">' + "\n"
            tmp += '<style  visible="1" opacity="0.5" focusColor="green" blurColor="blue" imagePath="" text="" fontSize="20" font="Arial" />' + "\n"
            tmp += '<action id="' + str(elem.action) + '"/>' + "\n"
            if elem.son:
                tmp += '<children>' + "\n"
                tmp += self.xmlRec(elem.son)
                tmp += '</children>' + "\n"
            tmp += '</box>' + "\n"
        return tmp

    # release : create a box
    # zoom in create box child
    def loadFile(self):
        filename = QFileDialog.getOpenFileName(None, \
                                               self.loadDialog, \
                                               QDir.currentPath(), \
                                               self.extensionDialog)
        if filename == '':
            return

        print filename
        
        self.parser = xml.parsers.expat.ParserCreate()
        self.parserCurrentBox = None

        def XMLstartElement(name, attrs):
            if name == 'box':
                x = QString(attrs['x']).toInt()
                y = QString(attrs['y']).toInt()
                width = QString(attrs['width']).toInt()
                height = QString(attrs['height']).toInt()
                
                if not x[1] or not y[1] or not width[1] or not height[1]:
                    print 'Warning : XML Attributes Parse Error'
                
                posStart = QPoint(x[0], y[0])
                posEnd = QPoint(x[0] + width[0], y[0] + height[0])
                tmpBox = Box(posStart, posEnd)
                
                tmpBox.father = self.father

                self.list.append(tmpBox)
                self.parserCurrentBox = tmpBox

            if name == 'children':
                self.father = self.list
                tmp = []
                self.list = tmp
                self.parserCurrentBox.son = tmp
                    
        def XMLendElement(name):
             if name == 'children':
                self.list = self.father
                self.father = self.list[0].father

        #def XMLcharData(data):
            # print 'Character data:', repr(data)

        self.parser.StartElementHandler = XMLstartElement
        self.parser.EndElementHandler = XMLendElement
        self.list = []
        self.father = None
        self.focus = None
        self.parser.ParseFile(open(filename, "r"))        
        self.repaint()
 
    def selectionMode(self):
        self.mode = Mode.selection

    def boxMode(self):
        self.mode = Mode.box

    def zoomIn(self):
        if self.focused:
            self.father = self.list
            if self.focused.son:
                self.list = self.focused.son
            else:
                self.list = []
                self.focused.son = self.list
            self.focused.focus = 0
            self.focused = None
            self.clipboard = None
            self.repaint()
        else:
            QMessageBox.information(self, 'IotBuilder', \
                                    'You have not selected any box.')

    def zoomOut(self):
        if self.father:
            self.list = self.father
            if self.focused:
                self.focused.focus = 0
            self.focused = None
            self.clipboard = None
            self.father = self.list[0].father
            self.repaint()
        else:
            QMessageBox.information(self, 'IotBuilder', \
                                    'You are on the top level.')

    def copyBox(self):
        if self.focused:
            self.clipboard = Box(self.focused.topLeft(), \
                                 self.focused.bottomRight())
            self.clipboard.father = self.focused.father

    def cutBox(self):
        if self.focused:
            self.copyBox()
            self.deleteFocusedBox()
            self.repaint()

    def pasteBox(self):
        if self.clipboard:
            copy = Box(self.clipboard.topLeft(), \
                       self.clipboard.bottomRight())
            copy.father = self.clipboard.father
            self.list.append(copy)
            self.repaint()

    def builderHelp(self):
        print 'builderHelp method'

    def shortcuts(self):
        print 'shortcuts method'

    def aboutUs(self):
        print 'aboutUs method'

    def quitBuilder(self):
        self.deleteLater()
        app.quit()

    def selectBox(self, pos):
        topBox = 0
        for box in self.list:
            if box.normalized().contains(pos):
                topBox = box
            box.focus = 0
        self.focused = topBox
        if topBox:
            topBox.focus = 1

    def selectNextBox(self):
        if self.focused and len(self.list) > 1:
            index = self.list.index(self.focused)
            self.focused.focus = 0
            self.focused = self.list[(index + 1) % len(self.list)]
            self.focused.focus = 1
        elif len(self.list):
            self.focused = self.list[0]
            self.focused.focus = 1
        self.repaint()

    def selectPreviousBox(self):
        length = len(self.list)
        if self.focused and length > 1:
            index = self.list.index(self.focused)
            if index == 0:
                index = length - 1
            else:
                index = index - 1
            self.focused.focus = 0
            self.focused = self.list[index]
            self.focused.focus = 1
        elif length > 0:
            self.focused = self.list[length - 1]
            self.focused.focus = 1
        self.repaint()

    def deleteFocusedBox(self):
        if self.focused:
            self.list.remove(self.focused)
            self.focused = None

    def mouseDoubleClickEvent(self, mouseEvent):
        if self.focused and self.mode == Mode.selection:
            self.zoomIn()

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
            elif keyEvent.key() == QtCore.Qt.Key_Delete:
                self.deleteFocusedBox()
            self.repaint()
        elif keyEvent.key() == QtCore.Qt.Key_Enter or \
            keyEvent.key() == QtCore.Qt.Key_Return:
            self.zoomIn()
        elif keyEvent.key() == QtCore.Qt.Key_Backspace:
            self.zoomOut()

    def onEdge(self, point, Box):
        if point.x() == Box.left():
            if point.y() >= Box.top() and point.y() <= Box.top() + self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeFDiagCursor)
                self.curs = 1
            elif point.y() <= Box.bottom() and point.y() >= Box.bottom() - self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeBDiagCursor)
                self.curs = 7
            else:
                QtGui.QMainWindow.setCursor(self, Qt.SizeHorCursor)
                self.curs = 8
            return 1
        if point.x() == Box.right():
            if point.y() >= Box.top() and point.y() <= Box.top() + self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeBDiagCursor)
                self.curs = 3
            elif point.y() <= Box.bottom() and point.y() >= Box.bottom() - self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeFDiagCursor)
                self.curs = 5
            else:
                QtGui.QMainWindow.setCursor(self, Qt.SizeHorCursor)
                self.curs = 4
            return 1

        if point.y() == Box.top():
            if point.x() >= Box.left() and point.x() <= Box.left() + self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeFDiagCursor)
                self.curs = 1
            elif point.x() <= Box.right() and point.x() >= Box.right() - self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeBDiagCursor)
                self.curs = 3
            else:
                QtGui.QMainWindow.setCursor(self, Qt.SizeVerCursor)
                self.curs = 2
            return 1
        if point.y() == Box.bottom():
            if point.x() >= Box.left() and point.x() <= Box.left() + self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeBDiagCursor)
                self.curs = 7
            elif point.x() <= Box.right() and point.x() >= Box.right() - self.tolerance:
                QtGui.QMainWindow.setCursor(self, Qt.SizeFDiagCursor)
                self.curs = 5
            else:
                QtGui.QMainWindow.setCursor(self, Qt.SizeVerCursor)
                self.curs = 6
            return 1
        self.curs = 0
        return 0

## 1     2     3
##
## 8 self.curs 4
##
## 7     6     5

    def mouseMoveEvent(self, mouseEvent):
        if self.leftButtonPressed:
            if self.focused and self.mode == Mode.selection:
                offset_x = mouseEvent.pos().x() - self.beginPos.x()
                offset_y = mouseEvent.pos().y() - self.beginPos.y()
                if self.curs ==  0:                    # deplacer la box
                    self.focused.translate(offset_x, offset_y)
                else:
                    topl = self.focused.topLeft()
                    botr = self.focused.bottomRight()
                    ind = self.list.index(self.focused)
                    if self.curs == 2 or self.curs == 1 or self.curs == 3: #resize higher border
                        topl.setY(mouseEvent.pos().y())
                    if self.curs == 6 or self.curs == 7 or self.curs == 5: #resize bottom border
                        botr.setY(mouseEvent.pos().y())
                    if self.curs == 8 or self.curs == 1 or self.curs == 7: #resize left border
                        topl.setX(mouseEvent.pos().x())
                    if self.curs == 4 or self.curs == 3 or self.curs == 5: #resize right border
                        botr.setX(mouseEvent.pos().x())
                    if topl.x() >= botr.x():
                        tmp = topl.x()
                        topl.setX(botr.x())
                        botr.setX(tmp)
                    if topl.y() >= botr.y():
                        tmp = topl.y()
                        topl.setY(botr.y())
                        botr.setY(tmp)
                    self.list[ind].setTopLeft(topl)
                    self.list[ind].setBottomRight(botr)
                    self.onEdge(mouseEvent.pos(), self.list[ind])

                self.beginPos = QPoint(mouseEvent.pos())

            self.endPos = QPoint(mouseEvent.pos())
            self.repaint()
        elif self.mode == Mode.selection:
            for box in self.list:
                if self.onEdge(mouseEvent.pos(), box) == 1:
                    return
            QtGui.QMainWindow.setCursor(self, Qt.ArrowCursor)

    def mousePressEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 1
            self.beginPos = QPoint(mouseEvent.pos())
            self.endPos = QPoint(mouseEvent.pos())
            if self.mode == Mode.selection:
                self.selectBox(mouseEvent.pos())
            self.repaint()
        else:
            QtGui.QMainWindow.mousePressEvent(self, mouseEvent)

    def mouseReleaseEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 0
            if self.mode == Mode.box:
                self.endPos = mouseEvent.pos()
                va1 = QPoint(min(self.beginPos.x(), mouseEvent.pos().x()), min(self.beginPos.y(), mouseEvent.pos().y()))
                va2 = QPoint(max(self.beginPos.x(), mouseEvent.pos().x()), max(self.beginPos.y(), mouseEvent.pos().y()))
                tmpBox = Box(va1, va2)
                tmpBox.father = self.father
                self.list.append(tmpBox)
                self.repaint()
        else:
            QtGui.QMainWindow.mouseReleaseEvent(self, mouseEvent)

    def paintEvent(self, event):
        paint = QtGui.QPainter()
        paint.begin(self)

        color = QtGui.QColor('#d4d4d4')
        colorFocus = QtGui.QColor('#aaaaaa')
        paint.setPen(color)

        paint.setBrush(QtGui.QColor(0, 0, 255, 80))              # RVB, opacity

        if self.leftButtonPressed and self.mode == Mode.box:
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




if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    builder = BuilderWidget()
    builder.setWindowOpacity(0.4)
    builder.setWindowFlags(QtCore.Qt.FramelessWindowHint)
    builder.show()
    sys.exit(app.exec_())
