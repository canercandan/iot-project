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

class BoxStyle(Node, dict):
    def __init__(self):
        self['visible'] = True
        self['opacity'] = 0.5
        self['imagePath'] = ""
        self['text'] = ""
        self['font'] = "Arial"
        self['fontSize'] = 20
        self['textColor'] = "black"
        self['focusColor'] = "yellow"
        self['blurColor'] = "black"

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
