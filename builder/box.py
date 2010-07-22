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
    def __init__(self):
        QRect.__init__(self)
        self.children = []                      # list of Boxes
        self.actionIdSet = 0
        self.attributeBuffer = ''
        self.boxEditor = BoxEditor()            # QDialog
        self.boxType = BoxType.CustomBox        # int

    # Standard constructor
    def initRegularBox(self, topLeft, bottomRight):
        self.setTopLeft(topLeft)
        self.setBottomRight(bottomRight)

    # Copy constructor # TODO: finih copy constructor
    def initFromRegularBox(self, box):
        self.setTopLeft(box.topLeft())
        self.setBottomRight(box.bottomRight())
        #self.setActionId(box.getActionId())
        #self.setAttribute(box.getAttribute())

    def initDomBox(self, domElement):
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

        # QDomNode
        domNode = elem.firstChild()
        while (not domNode.isNull()):
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
        boxNode = childElem.firstChild()
        while (not boxNode.isNull()):
            boxElem = boxNode.toElement()
            if boxElem and boxElem.tagName() == 'box':
                box = Box()
                box.initDomBox(boxElem)
                self.children.append(box)
            boxNode = boxNode.nextSibling()

    # Input: QDomDocument domDoc
    # Output: QDomElement
    def createXMLNode(self, domDoc):
        # QDomElement
        boxElem = domDoc.createElement('box')

        geometryFunctions = {
                "x" : self.x,
                "y" : self.y,
                "width" : self.width,
                "height" : self.height
            }

        # Setting box attributes
        boxElem.setAttribute('type', self.boxType)
        for k, v in geometryFunctions.iteritems():
            boxElem.setAttribute(k, v())

        # Adding action
        action = domDoc.createElement('action')
        boxElem.appendChild(action)

        # Adding Style
        style = domDoc.createElement('style')
        boxElem.appendChild(style)

        # Adding Children
        if self.children:
            children = domDoc.createElement('children')
            for child in self.children:
                children.appendChild(child.createXMLNode(domDoc))
            boxElem.appendChild(children)

        return boxElem

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
