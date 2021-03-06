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
from boxeditor import BoxEditor
from boxstyle import BoxStyle

class BoxType:
    DefaultBox = 0
    CustomBox = 1
    MenuBox = 2

class Box(QRect, Node):
    def __init__(self, builder):
        QRect.__init__(self)
        self.children = []                      # list of Boxes
        self.actionIdSet = 0
        self.attributeBuffer = ''
        self.boxEditor = BoxEditor(builder)     # QDialog
        self.boxType = BoxType.CustomBox        # int
        self.bufferedAttributes = {}            # dictionnary
	self.builder = builder

    # Standard constructor
    def initRegularBox(self, topLeft, bottomRight):
        self.setTopLeft(topLeft)
        self.setBottomRight(bottomRight)

    # Copy constructor # TODO: finish copy constructor
    def initFromRegularBox(self, box):
        self.setTopLeft(box.topLeft())
        self.setBottomRight(box.bottomRight())
        self.setActionId(box.getActionId())
        self.setAttributes(box.getAttributes())
        self.boxEditor.setStyle(box.boxEditor.getStyle())

    def initDomBox(self, domElement):
        self.initializeFromXml(domElement)

    # QDomElement elem
    def initializeFromXml(self, elem):
        if elem.hasAttribute('type'):
            self.boxtype = elem.attribute('type')

        geometryFunctions = {
            'x' : self.setX,
            'y' : self.setY,
            'width' : self.setWidth,
            'height' : self.setHeight }

        for k, v in geometryFunctions.iteritems():
            if elem.hasAttribute(k):
                attr = elem.attribute(k).toInt()
                if attr[1]: # if conversion is OK
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
        if childElem.hasAttribute('id'):
            self.setActionId(childElem.attribute('id'))
            childElem.removeAttribute('id')
            # QDomNamedNodeMap attributes
            attributes = childElem.attributes()
            myDict = {}
            for i in range(attributes.count()):
                domNode = attributes.item(i)
                myDict[domNode.nodeName()] = domNode.nodeValue()
            self.setAttributes(myDict)

    def parseStyle(self, childElem):
        boxstyle = BoxStyle()
        boxstyle.initializeFromXml(childElem)
        self.boxEditor.setStyle(boxstyle)

    # QDomElement chilElem
    def createChildren(self, childElem):
        boxNode = childElem.firstChild()
        while (not boxNode.isNull()):
            boxElem = boxNode.toElement()
            if boxElem and boxElem.tagName() == 'box':
                box = Box(self.builder) #parametre a verifier
                box.initDomBox(boxElem)
                self.children.append(box)
            boxNode = boxNode.nextSibling()

    # Input: QDomDocument domDoc
    # Output: QDomElement
    def createXMLNode(self, domDoc):
        # QDomElement
        boxElem = domDoc.createElement('box')

        geometryFunctions = {
                'x' : self.x,
                'y' : self.y,
                'width' : self.width,
                'height' : self.height
            }

        # Setting box attributes
        boxElem.setAttribute('type', self.boxType)
        for k, v in geometryFunctions.iteritems():
            boxElem.setAttribute(k, v())

        # Adding action
        action = domDoc.createElement('action')
        action.setAttribute('id', self.getActionId())
        attributes = self.getAttributes()
        for key, value in attributes.iteritems():
            action.setAttribute(key, value)
        boxElem.appendChild(action)

        # Adding Style
        boxstyle = self.boxEditor.getStyle()
        boxElem.appendChild(boxstyle.createXMLNode(domDoc))

        # Adding Children
        if self.children:
            children = domDoc.createElement('children')
            for child in self.children:
                children.appendChild(child.createXMLNode(domDoc))
            boxElem.appendChild(children)
        return boxElem

    def getActionId(self):
        return self.boxEditor.ui.listWidget.currentItem().text()

    def getType(self):
        return self.boxEditor.getType()

    def getAttributes(self):
        return self.boxEditor.getAttributes()

    def setActionId(self, boxType):
        for i in range(self.boxEditor.ui.listWidget.count()):
            if boxType == self.boxEditor.ui.listWidget.item(i).text():
                self.boxEditor.ui.listWidget.setCurrentRow(i)
                if self.bufferedAttributes:
                    self.setAttributes(self.bufferedAttributes)
                self.actionIdSet = 1
                return
        raise NameError('Action id "', boxType, '" not found.')

    def setAttribute(self, key, value):
        if self.actionIdSet == 1:
            self.boxEditor.setAttribute(key, value)
        else :
            # buffer attribute
            self.bufferedAttributes[key] = value

    # attributes is a dictionnary
    def setAttributes(self, attributes):
        for key, value in attributes.iteritems():
            self.boxEditor.setAttribute(key, value)

    def editBox(self):
        self.boxEditor.open()

    def deleteBoxEditor(self):
        self.boxEditor.deleteLater()

    def childNotificator(self):
	if self.children:
            print "I have a child!"
