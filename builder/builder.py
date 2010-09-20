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

from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4.QtXml import *

from box import *
from toolbar import *
from boxeditor import *

class Mode:
    box = 0
    selection = 1

class DefaultColors:
    text  = 'black'
    blur  = 'yellow'
    focus = 'orange'

class View():
    def __init__(self, parentView):
        self.currentBox = None          # Box
        self.clipboard = None           # Box
        self.parentView = parentView    # View
        if parentView and parentView.currentBox.children:
            self.boxes = parentView.currentBox.children
        else:
            self.boxes = []             # list of Boxes

class BuilderWidget(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        QtGui.QMainWindow.setAttribute(self, Qt.WA_AlwaysShowToolTips)

        try:
            self.toolbar = Toolbar(self)
            self.addToolBar(Qt.LeftToolBarArea, self.toolbar)
        except:
            print "Unexpected error:", sys.exc_info()[0]
            raise

        self.init()
        self.createMenu()
        self.setGeometry(200, 200, 700, 700)
        self.setWindowTitle('IotBuilder')
        self.setMouseTracking(1)
        self.saveDialog = QObject.tr(self, 'Save xml file')
        self.loadDialog = QObject.tr(self, 'Open xml file')
        self.extensionDialog = QObject.tr(self, 'Xml Files') + ' (*.xml)'
        self.extension = '.xml'
        self.defaultTextColor = QColor(DefaultColors.text)
        self.defaultBlurColor = QColor(DefaultColors.blur)
        self.defaultFocusColor = QColor(DefaultColors.focus)
        self.defaultBlurColor.setAlpha(80)
        self.defaultFocusColor.setAlpha(80)

    def init(self):
        self.tolerance = 0
        self.curs = 0
        self.mode = Mode.selection
        self.leftButtonPressed = 0
        self.beginPos = QPoint()
        self.endPos = QPoint()
        self.rootView = View(None)
        self.currentView = self.rootView
        self.views = [self.rootView]
        #self.keyboardTest(QPoint(0, 0), QPoint(400, 100))

    def keyboardTest(self, topLeft, bottomRight):
        my_keymap = "AZERTYUIOPQSDFGHJKLMWXCVBN 0123456789"
        nb_col = 10
        nb_line = 4
        sizex = bottomRight.x() - topLeft.x()
        sizey = bottomRight.y() - topLeft.y()
        caseSizex = sizex // nb_col
        caseSizey = sizey // nb_line
        col = 0
        line = 0
        for c in my_keymap:
            if col >= nb_col:
                col = 0
                line += 1
            if line >= nb_line:
                print "keymap too big"
                return

            tmpx = QPoint(topLeft.x() + col * caseSizex, topLeft.y() + line * caseSizey)
            tmpy = QPoint(topLeft.x() + (col + 1) * caseSizex, topLeft.y() + (line + 1) * caseSizey)
            tmpBox = self.createRegularBox(tmpx, tmpy)
            col += 1
            self.repaint()

    def createRegularBox(self, topLeft, bottomRight):
        box = Box(self)
        box.initRegularBox(topLeft, bottomRight)
        self.currentView.boxes.append(box)
        if self.currentView != self.rootView:
            self.currentView.parentView.currentBox.children.append(box)
        return box

    def createDomBox(self, domElement):
        box = Box(self)
        box.initDomBox(domElement)
        self.currentView.boxes.append(box)

    def createMenu(self):
        self.menu = QMainWindow.createPopupMenu(self)

    def newFile(self):
        if not self.currentView.boxes and self.currentView == self.rootView:
            return
        r = QMessageBox.question(self, 'IotBuilder',
                                 QObject.tr(self, 'Are you sure to clean all boxes ?'),
                                 QMessageBox.Ok, QMessageBox.Cancel)
        if r == QMessageBox.Cancel:
            return
        self.init()
        self.repaint()

    def getFilenameFromFullPath(self, filename):
        result = QString(filename).section(QDir.separator(), -1)
        result = QString(result).section('.', 0, 0)
        return result

    def overwriteQuestion(self, filename):
        shortFilename = QString(filename).section(QDir.separator(), -1)
        directory = QString(filename).section(QDir.separator(), -2, -2)
        return QMessageBox.question(self, 'IotBuilder',
                                    QString(
                                        QObject.tr(self, '<b>A file named "%1" already exists.<br />Do you want to replace it ?</b><br /><br />'
                                                   'The file already exists in "%2".<br />Replacing it will overwrite its contents.')
                                            ).arg(shortFilename).arg(directory),
                                    QMessageBox.Ok, QMessageBox.Cancel)

    def loadFile(self):
        if self.currentView.boxes or self.currentView != self.rootView:
            r = QMessageBox.question(self, 'IotBuilder',
                                     QObject.tr(self, 'You are going to lose all of your work... Are you sure ?'),
                                     QMessageBox.Ok, QMessageBox.Cancel)
            if r == QMessageBox.Cancel:
                return
            else:
                self.init()

        filename = QFileDialog.getOpenFileName(None,
                                               self.loadDialog,
                                               QDir.currentPath(),
                                               self.extensionDialog)
        if filename == '':
            return

        qfile = QFile(filename)
        doc = QDomDocument("XmlBox")

        flags = QIODevice.OpenMode(QIODevice.ReadOnly)
        flags.__and__(QIODevice.Text)
        if not qfile.open(flags):
            QMessageBox.warning(self, 'IotBuilder', QObject.tr(self, 'Failed to load file.'))
            return

        if not doc.setContent(qfile):
            qfile.close()
            QMessageBox.warning(self, 'IotBuilder', QObject.tr(self, 'Unable to setContent.'))
            return

        qfile.close()

        # QDomElement
        root = doc.documentElement()
        if root.tagName() != 'boxes' and root.tagName() != 'menu':
            QMessageBox.warning(self, 'IotBuilder', QObject.tr(self, 'Error.'))
            return

        # TODO: Do not forget to use programID
        programId = root.attribute("id")

        # QDomNode
        boxNode = root.firstChild()
        while (not boxNode.isNull()):
            boxElem = boxNode.toElement()
            if boxElem and boxElem.tagName() == 'box':
                self.createDomBox(boxElem)
            boxNode = boxNode.nextSibling()
        self.repaint()

    def saveFile(self):
        if not self.currentView.boxes and self.currentView == self.rootView:
            QMessageBox.information(self, 'IotBuilder', QObject.tr(self, 'Nothing to save'))
            return

        filename = QFileDialog.getSaveFileName(None,
                                               self.saveDialog,
                                               QDir.currentPath(),
                                               self.extensionDialog)
        if filename == '':
            return
        if not QString(filename).endsWith(self.extension):
            filename.append(self.extension)
            if QDir(QDir.currentPath()).exists(filename):
                r = self.overwriteQuestion(filename)
                if r == QMessageBox.Cancel:
                    return

        qfile = QFile(filename)
        if not qfile.open(QIODevice.WriteOnly | QIODevice.Text):
            QMessageBox.warning(self, 'IotBuilder', QObject.tr(self, 'Unable to open file.'))
            return

        doc = QDomDocument('XmlBox')
        root = doc.createElement('boxes')
        root.setAttribute('id', self.getFilenameFromFullPath(filename))
        scrGeo = QApplication.desktop().screenGeometry()
        root.setAttribute('resolution-x', scrGeo.x())
        root.setAttribute('resolution-y', scrGeo.y())
        root.setAttribute('resolution-width', scrGeo.width())
        root.setAttribute('resolution-height', scrGeo.height())
        doc.appendChild(root)

        for box in self.rootView.boxes:
            root.appendChild(box.createXMLNode(doc))

        out = QTextStream(qfile)
        out << doc.toString()
        qfile.close()

    def selectionMode(self):
        self.mode = Mode.selection

    def boxMode(self):
        self.mode = Mode.box

    def selectBox(self, pos):
        topBox = None
        for box in self.currentView.boxes:
            if box.normalized().contains(pos):
                topBox = box
        self.currentView.currentBox = topBox

    def selectPreviousBox(self):
        length = len(self.currentView.boxes)
        if self.currentView.currentBox and length > 1:
            index = self.currentView.boxes.index(self.currentView.currentBox)
            if index == 0:
                index = length - 1
            else:
                index = index - 1
            self.currentView.currentBox = self.currentView.boxes[index]
        elif length > 0:
            self.currentView.currentBox = self.currentView.boxes[length - 1]
        self.repaint()

    def selectNextBox(self):
        if self.currentView.currentBox and len(self.currentView.boxes) > 1:
            index = self.currentView.boxes.index(self.currentView.currentBox)
            self.currentView.currentBox = self.currentView.boxes[(index + 1) % len(self.currentView.boxes)]
        elif len(self.currentView.boxes):
            self.currentView.currentBox = self.currentView.boxes[0]
        self.repaint()

    def editBox(self):
        if self.currentView.currentBox:
            self.currentView.currentBox.editBox()
        else:
            QMessageBox.information(self, 'IotBuilder', QObject.tr(self, 'You have not selected any box.'))

    def zoomIn(self):
        if self.currentView.currentBox:
            self.currentView = View(self.currentView)
            self.repaint()
        else:
            QMessageBox.information(self, 'IotBuilder', QObject.tr(self, 'You have not selected any box.'))

    def zoomOut(self):
        if self.currentView.parentView:
            self.currentView = self.currentView.parentView
            self.repaint()
        else:
            QMessageBox.information(self, 'IotBuilder', QObject.tr(self, 'You are on the top level.'))

    def copyBox(self):
        if self.currentView.currentBox:
            self.currentView.clipboard = Box(self)
            self.currentView.clipboard.initFromRegularBox(self.currentView.currentBox)

    def cutBox(self):
        if self.currentView.currentBox:
            self.copyBox()
            self.deleteCurrentBoxBox()
            self.repaint()

    def pasteBox(self):
        if self.currentView.clipboard:
            box = self.createRegularBox(self.currentView.clipboard.topLeft(),
                                        self.currentView.clipboard.bottomRight())
            box.initFromRegularBox(self.currentView.clipboard)
            self.repaint()

    def builderHelp(self):
        print 'builderHelp method'

    def quitBuilder(self):
        self.deleteLater()
        self.toolbar.deleteLater()
        for box in self.rootView.boxes:
            box.boxEditor.deleteLater()
        app.quit()

    def deleteCurrentBoxBox(self):
        if self.currentView.currentBox:
            self.currentView.boxes.remove(self.currentView.currentBox)
            self.currentView.currentBox = None

    def keyPressEvent(self, keyEvent):
        if self.currentView.currentBox:
            if keyEvent.key() == QtCore.Qt.Key_Left:
                self.currentView.currentBox.translate(-1, 0)
            elif keyEvent.key() == QtCore.Qt.Key_Right:
                self.currentView.currentBox.translate(1, 0)
            elif keyEvent.key() == QtCore.Qt.Key_Up:
                self.currentView.currentBox.translate(0, -1)
            elif keyEvent.key() == QtCore.Qt.Key_Down:
                self.currentView.currentBox.translate(0, 1)
            elif keyEvent.key() == QtCore.Qt.Key_Delete:
                self.deleteCurrentBoxBox()
            elif keyEvent.key() == QtCore.Qt.Key_Enter or keyEvent.key() == QtCore.Qt.Key_Return:
                self.zoomIn()
        elif keyEvent.key() == QtCore.Qt.Key_Backspace:
            self.zoomOut()
        self.repaint()

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
            if self.currentView.currentBox and self.mode == Mode.selection:
                offset_x = mouseEvent.pos().x() - self.beginPos.x()
                offset_y = mouseEvent.pos().y() - self.beginPos.y()
                if self.curs ==  0:                    # deplacer la box
                    self.currentView.currentBox.translate(offset_x, offset_y)
                else:
                    topl = self.currentView.currentBox.topLeft()
                    botr = self.currentView.currentBox.bottomRight()
                    ind = self.currentView.boxes.index(self.currentView.currentBox)
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
                    self.currentView.boxes[ind].setTopLeft(topl)
                    self.currentView.boxes[ind].setBottomRight(botr)
                    self.onEdge(mouseEvent.pos(), self.currentView.boxes[ind])

                self.beginPos = QPoint(mouseEvent.pos())

            self.endPos = QPoint(mouseEvent.pos())
            self.repaint()
        elif self.mode == Mode.selection:
            for box in self.currentView.boxes:
                if self.onEdge(mouseEvent.pos(), box) == 1:
                    return
                QtGui.QMainWindow.setCursor(self, Qt.ArrowCursor)

    def contextMenuEvent(self, contextMenuEvent):
        self.menu.exec_(QCursor.pos())

    def mousePressEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 1
            self.beginPos = QPoint(mouseEvent.pos())
            self.endPos = QPoint(mouseEvent.pos())
            if self.mode == Mode.selection:
                self.selectBox(mouseEvent.pos())
                self.repaint()

    def mouseDoubleClickEvent(self, mouseEvent):
        if self.mode == Mode.selection:
            self.editBox()

    def mouseReleaseEvent(self, mouseEvent):
        if mouseEvent.button() == QtCore.Qt.LeftButton:
            self.leftButtonPressed = 0
            if self.mode == Mode.box:
                self.endPos = mouseEvent.pos()
                va1 = QPoint(min(self.beginPos.x(), mouseEvent.pos().x()), min(self.beginPos.y(), mouseEvent.pos().y()))
                va2 = QPoint(max(self.beginPos.x(), mouseEvent.pos().x()), max(self.beginPos.y(), mouseEvent.pos().y()))
                self.createRegularBox(va1, va2)
                self.repaint()

    # TODO: set alpha channel from boxEditor
    def configurePainterForBox(self, painter, boxEditor, focus):
        # Setting brush
        if focus == True:
            if QColor(boxEditor.focusColor).isValid():
                customFocusColor = QColor(boxEditor.focusColor)
                customFocusColor.setAlpha(80)
                painter.setBrush(QColor(customFocusColor))
            else:
                painter.setBrush(self.defaultFocusColor)
        else:
            if QColor(boxEditor.blurColor).isValid():
                customBlurColor = QColor(boxEditor.blurColor)
                customBlurColor.setAlpha(80)
                painter.setBrush(QColor(customBlurColor))
            else:
                painter.setBrush(self.defaultBlurColor)

        # Setting pen
        if QColor(boxEditor.textColor).isValid():
            customTextColor = QColor(boxEditor.textColor)
            customTextColor.setAlpha(80)
            painter.setPen(QColor(customTextColor))
        else:
            painter.setPen(self.defaultTextColor)

    def paintEvent(self, event):
        painter = QtGui.QPainter()
        painter.begin(self)

        painter.setPen(self.defaultTextColor)
        painter.setBrush(self.defaultBlurColor)

        if self.leftButtonPressed and self.mode == Mode.box:
            painter.drawRect(self.beginPos.x(), self.beginPos.y(), self.endPos.x() - self.beginPos.x(), self.endPos.y() - self.beginPos.y())

        if self.currentView.boxes:
            for box in self.currentView.boxes:
                self.configurePainterForBox(painter, box.boxEditor, (box == self.currentView.currentBox))
                if box.boxEditor.ui.roundedCheckBox.isChecked():
                    painter.drawRoundRect(box)
                else:
                    painter.drawRect(box)
                if not box.boxEditor.ui.textLineEdit.text().isEmpty():
                    painter.drawText(box, Qt.AlignCenter, box.boxEditor.ui.textLineEdit.text())
        painter.end()


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)

    qtTranslator = QTranslator()
    qtTranslator.load('qt_' + QLocale.system().name(), QLibraryInfo.location(QLibraryInfo.TranslationsPath))
    app.installTranslator(qtTranslator)

    iotTranslator = QTranslator();
    iotTranslator.load('iot_' + QLocale.system().name())
    app.installTranslator(iotTranslator)

    builder = BuilderWidget()
    builder.setWindowOpacity(0.4)
    builder.setWindowFlags(QtCore.Qt.FramelessWindowHint)
    builder.showFullScreen()
    sys.exit(app.exec_())
