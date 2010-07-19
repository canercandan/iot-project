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

from boxeditor import BoxEditor

class Box(QRect):
    def __init__(self, topLeft, bottomRight):
        QRect.__init__(self, topLeft, bottomRight)
        self.son = None
        self.focus = None
        self.father = None
        self.actionIdSet = 0
        self.attributeBuffer = ''
        self.boxEditor = BoxEditor()

    def getActionId(self):
        return self.boxEditor.ui.tabs.tabText(self.boxEditor.ui.tabs.currentIndex())

    def getAttribute(self):
        return self.boxEditor.getAttribute()

    def setActionId(self, boxType):
        for i in range(self.boxEditor.ui.tabs.count()):
            if boxType == self.boxEditor.ui.tabs.tabText(i):
                self.boxEditor.ui.tabs.setCurrentIndex(i)
                if self.attributeBuffer != '':
                    self.boxEditor.setAttribute(self.attributeBuffer)
                self.actionIdSet = 1
                return
        raise NameError('Action id "', boxType, '" not found.')

    def setAttribute(self, attribute):
        if self.actionIdSet == 1 and attribute != '':
            self.boxEditor.setAttribute(attribute)
        else:
            self.attributeBuffer = attribute

    def editBox(self):
        self.boxEditor.open()

    def deleteBoxEditor(self):
        self.boxEditor.deleteLater()
