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

class BoxType:
    DefaultBox = 0
    CustomBox = 1
    MenuBox = 2

class Box(QRect):
    def __init__(self, topLeft, bottomRight):
        QRect.__init__(self, topLeft, bottomRight)
        self.son = None
        self.focus = None
        self.father = None
        self.actionIdSet = 0
        self.attributeBuffer = ''
        self.boxEditor = BoxEditor()
        self.boxType = BoxType.CustomBox

    def __init__(self, domElement, parent):
        QRect.__init__(self)
        self.son = None
        self.focus = None
        self.father = parent
        self.actionIdSet = 0
        self.attributeBuffer = ''
        self.boxEditor = BoxEditor()
        self.boxType = BoxType.CustomBox
        self.initializeFromXml(domElement)

    # QDomElement elem
    def initializeFromXml(self, elem):
        if elem.hasAttribute("type"):
            self.boxtype = elem.attribute("type")

        geometryFunctions = {
            "x" : self.setX,
            "y" : self.setY,
            "width" : self.setWidth,
            "height" : self.setHeight }

        for k, v in geometryFunctions.iteritems():
            if elem.hasAttribute(k):
                attr = elem.attribute(k).toInt()
                if attr[1]:
                    v(attr[0])

        domNode = elem.firstChild()
        while (domNode):
            print 'child in init'
            childElem = domNode.toElement()
            if childElem:
                tag = childElem.tagName()
                if tag == 'action':
                    self.parseAction(childElem)
                elif tag == 'style':
                    self.parseStyle(childElem)
                elif tag == 'children':
                    self.createChildren(childElem)
            domNode = domNode.nextSibling()

    def parseAction(self, childElem):
        print 'id = ', childElem.attribute('id')

    def parseStyle(self, childElem):
        print 'style = '

    # QDomElement chilElem
    def createChildren(self, childElem):
        print 'Creating children'
        boxNode = childElem.firstChild()
        while (boxNode):
            print 'one child'
            boxElem = boxNode.toElement()
            if boxElem and boxElem.tagName() == 'box':
                self.son.append(Box(boxElem, self))
            boxNode = boxNode.nextSibling()

    # Input: QDomDocument domDoc
    # Output: QDomElement
    def createXMLNode(self, domDoc):
        domElem = domDoc.createElement('box')

        geometryFunctions = {
                "x" : self.x,
                "y" : self.y,
                "width" : self.width,
                "height" : self.height
            }

        for k, v in geometryFunctions.iteritems():
            domElem.setAttribute(k, v())

        for child in self.son:
            domElem.appendChild(child.createXMLNode(domDoc))

        return domElem

    def getActionId(self):
        return self.boxEditor.ui.tabs.tabText(self.boxEditor.ui.tabs.currentIndex())

    def getType(self):
        return self.boxEditor.getType()

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
