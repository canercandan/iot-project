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
    def __init__(self, builder):
        QtGui.QDialog.__init__(self, builder)
        self.ui = Ui_BoxEditor()
        self.ui.setupUi(self)

        self['rounded'] = False
        self['focusColor'] = 'yellow'
        self['blurColor'] = 'black'
        self['textColor'] = 'black'
        self['opacity'] = 0.5
        self['text'] = ''
        self['imagePath'] = ''

        self.getDictionnary = {
            QtGui.QApplication.translate('BoxEditor', 'Click')    :   self.getClickAttributes,
            QtGui.QApplication.translate('BoxEditor', 'Zoom')     :   self.getZoomAttributes,
            QtGui.QApplication.translate('BoxEditor', 'Read')     :   self.getReadAttributes,
            QtGui.QApplication.translate('BoxEditor', 'Write')    :   self.getWriteAttributes,
            QtGui.QApplication.translate('BoxEditor', 'PopMenu')  :   self.getPopMenuAttributes }

        self.setDictionnary = {
            QtGui.QApplication.translate('BoxEditor', 'Click')    :   self.setClickAttribute,
            QtGui.QApplication.translate('BoxEditor', 'Zoom')     :   self.setZoomAttribute,
            QtGui.QApplication.translate('BoxEditor', 'Read')     :   self.setReadAttribute,
            QtGui.QApplication.translate('BoxEditor', 'Write')    :   self.setWriteAttribute,
            QtGui.QApplication.translate('BoxEditor', 'PopMenu')  :   self.setPopMenuAttribute }

    # One attribute for the moment but this is extensible
    def getAttributes(self):
        for tabTitle in self.getDictionnary:
            if tabTitle == self.ui.listWidget.currentItem().text():
                return self.getDictionnary[tabTitle]()

    def getClickAttributes(self):
        return {'type' : QString.number(self.ui.clickComboBox.currentIndex())}

    def getPopMenuAttributes(self):
        return {'MenuId' : QString.number(self.ui.popMenuComboBox.currentIndex())}

    def getReadAttributes(self):
        return {'time' : QString.number(self.ui.readDoubleSpinBox.value())}

    def getWriteAttributes(self):
        return {'buffer' : self.ui.writeLineEdit.text()}

    def getZoomAttributes(self):
        return {'isZoom' : QString.number(self.ui.zoomComboBox.currentIndex())}

    def setAttribute(self, key, value):
        for tabTitle in self.getDictionnary:
            if tabTitle == self.ui.listWidget.currentItem().text():
                self.setDictionnary[tabTitle](key, value)

    def setClickAttribute(self, key, value):
        if key != 'type':
            print 'Unknown key'
            return

        r = QString(value).toInt()
        if not r[1]:
            return
        if r[0] < self.ui.clickComboBox.count():
            self.ui.clickComboBox.setCurrentIndex(r[0])

    def setPopMenuAttribute(self, key, value):
        if key != 'MenuId':
            print 'Unknown key'
            return

        r = QString(value).toInt()
        if not r[1]:
            return
        if r[0] < self.ui.popMenuComboBox.count():
            self.ui.popMenuComboBox.setCurrentIndex(r[0])

    def setReadAttribute(self, key, value):
        if key != 'time':
            print 'Unknown key'
            return

        r = QString(value).toFloat()
        if not r[1]:
            return
        self.ui.readDoubleSpinBox.setValue(r[0])

    def setWriteAttribute(self, key, value):
        if key != 'buffer':
            print 'Unknown key'
            return
        self.ui.writeLineEdit.setText(value)

    def setZoomAttribute(self, key, value):
        if key != 'isZoom':
            print 'Unknown key'
            return

        r = QString(value).toInt()
        if not r[1]:
            return
        if r[0] < self.ui.zoomComboBox.count():
            self.ui.zoomComboBox.setCurrentIndex(r[0])
