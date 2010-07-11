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

import PyQt4
from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *
from PyQt4.QtGui import QToolBar

import icons_rc

class s():
    def __init__(self, pixPath, tooltip, slot):
        self.pixPath = pixPath
        self.tooltip = tooltip
        self.slot = slot

class Toolbar(QtGui.QToolBar):
    def __init__(self, parent):
        QtGui.QToolBar.__init__(self, 'Display toolbar', parent)

        self.buttons = [ \
            s(':/pix/new_file', 'New file (Ctrl+N)', parent.newFile), \
            s(':/pix/load_file', 'Load file (Ctrl+L)', parent.loadFile), \
            s(':/pix/save_file', 'Save file (Ctrl+N)', parent.saveFile), \
            s('', '', None), \
            s(':/pix/selection', 'Selection mode (S)', parent.selectionMode), \
            s(':/pix/box', 'Box mode (B)', parent.boxMode), \
            s(':/pix/zoom_in', 'Zoom in (+)', parent.zoomIn), \
            s(':/pix/zoom_out', 'Zoom out (-)', parent.zoomOut), \
            s('', '', None), \
            s(':/pix/copy_box', 'Copy box (Ctrl+C)', parent.copyBox), \
            s(':/pix/cut_box', 'Cut box (Ctrl+X)', parent.cutBox), \
            s(':/pix/paste_box', 'Paste box (Ctrl+V)', parent.pasteBox), \
            s('', '', None), \
            s(':/pix/help', 'Builder help (F1)', parent.builderHelp), \
            s(':/pix/shortcuts', 'Shortcuts (F2)', parent.shortcuts), \
            s(':/pix/about', 'About us (F3)', parent.aboutUs), \
            s(':/pix/quit', 'Quit (Ctrl+Q)', parent.quitBuilder)]

        for item in self.buttons:
            if item.slot == None:
                QtGui.QToolBar.addSeparator(self)
            else:
                action = QtGui.QAction(QtGui.QIcon(item.pixPath), '', self)
                QtGui.QAction.setToolTip(action, item.tooltip)
                QtGui.QToolBar.addAction(self, action)
                QObject.connect(action, SIGNAL("triggered()"), item.slot)
