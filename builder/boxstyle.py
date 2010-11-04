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

from node import Node
from builder import DefaultColors # const values

class BoxStyle(Node, dict):
    def __init__(self):
        self['rounded'] = False
        self['focusColor'] = DefaultColors.focus
        self['blurColor'] = DefaultColors.blur
        self['textColor'] = DefaultColors.text
        self['opacity'] = str(0.5)
        self['text'] = ''
        self['imagePath'] = ''
	self['font'] = ''

    def initializeFromXml(self, elem):
        for key, value in self.iteritems():
            if elem.hasAttribute(key):
                self[key] = elem.attribute(key)

    def createXMLNode(self, domDoc):
        boxElem = domDoc.createElement('style')
        # Setting box style attributes
        for key, value in self.iteritems():
            boxElem.setAttribute(key, value)
        return boxElem
