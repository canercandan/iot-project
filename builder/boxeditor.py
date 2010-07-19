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

from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from BoxEditor_ui import Ui_BoxEditor

import box

class BoxEditor(QtGui.QDialog):
    def __init__(self):
        QtGui.QDialog.__init__(self)
        self.ui = Ui_BoxEditor()
        self.ui.setupUi(self)

        self.getDictionnary = {
            QtGui.QApplication.translate("BoxEditor", 'Cancel')   :   self.getCancelAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Click')    :   self.getClickAttribute,
            QtGui.QApplication.translate("BoxEditor", 'ExecMenu') :   self.getExecMenuAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Move')     :   self.getMoveAttribute,
            QtGui.QApplication.translate("BoxEditor", 'PopMenu')  :   self.getPopMenuAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Read')     :   self.getReadAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Valid')    :   self.getValidAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Write')    :   self.getWriteAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Zoom')     :   self.getZoomAttribute }

        self.setDictionnary = {
            QtGui.QApplication.translate("BoxEditor", 'Cancel')   :   self.setCancelAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Click')    :   self.setClickAttribute,
            QtGui.QApplication.translate("BoxEditor", 'ExecMenu') :   self.setExecMenuAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Move')     :   self.setMoveAttribute,
            QtGui.QApplication.translate("BoxEditor", 'PopMenu')  :   self.setPopMenuAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Read')     :   self.setReadAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Valid')    :   self.setValidAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Write')    :   self.setWriteAttribute,
            QtGui.QApplication.translate("BoxEditor", 'Zoom')     :   self.setZoomAttribute }

    def getAttribute(self):
        for tabTitle in self.getDictionnary:
            if tabTitle == self.ui.tabs.tabText(self.ui.tabs.currentIndex()):
                return self.getDictionnary[tabTitle]()

    def getCancelAttribute(self):
        return ''

    def getClickAttribute(self):
        return QString.number(self.ui.clickComboBox.currentIndex())

    def getExecMenuAttribute(self):
        return ''

    def getMoveAttribute(self):
        return ''

    def getPopMenuAttribute(self):
        return ''

    def getReadAttribute(self):
        return QString.number(self.ui.readDoubleSpinBox.value())

    def getValidAttribute(self):
        return ''

    def getWriteAttribute(self):
        return self.ui.writeLineEdit.text()

    def getZoomAttribute(self):
        return QString.number(self.ui.zoomComboBox.currentIndex())

    def setAttribute(self, attribute):
        for tabTitle in self.getDictionnary:
            if tabTitle == self.ui.tabs.tabText(self.ui.tabs.currentIndex()):
                self.setDictionnary[tabTitle](attribute)

    # TODO
    def setCancelAttribute(self, attribute):
        print ''

    def setClickAttribute(self, attribute):
        r = QString(attribute).toInt()
        if not r[1]:
            return
        if r[0] < self.ui.clickComboBox.count():
            self.ui.clickComboBox.setCurrentIndex(r[0])

    # TODO
    def setExecMenuAttribute(self, attribute):
        print ''

    # TODO
    def setMoveAttribute(self, attribute):
        print ''

    # TODO
    def setPopMenuAttribute(self, attribute):
        print ''

    def setReadAttribute(self, attribute):
        r = QString(attribute).toFloat()
        if not r[1]:
            return
        self.ui.readDoubleSpinBox.setValue(r[0])

    # TODO
    def setValidAttribute(self, attribute):
        print ''

    def setWriteAttribute(self, attribute):
        self.ui.writeLineEdit.setText(attribute)

    def setZoomAttribute(self, attribute):
        r = QString(attribute).toInt()
        if not r[1]:
            return
        if r[0] < self.ui.zoomComboBox.count():
            self.ui.zoomComboBox.setCurrentIndex(r[0])
