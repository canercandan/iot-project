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
from PyQt4.QtGui import QToolBar

from shortcuts import Shortcuts

import icons_rc

# C struct style
class s():
    def __init__(self, pixPath, tooltip, shortcut, slot):
        self.pixPath = pixPath
        self.tooltip = tooltip
        self.shortcut = shortcut
        self.slot = slot

class Toolbar(QtGui.QToolBar):
    def __init__(self, parent):
        QtGui.QToolBar.__init__(self, 'Display toolbar')
        QtGui.QWidget.setAttribute(self, Qt.WA_AlwaysShowToolTips)

        self.buttons = [
            s(':/pix/new_file', QObject.tr(self, 'New file'), 'Ctrl+N', parent.newFile),
            s(':/pix/load_file', QObject.tr(self, 'Load file'), 'Ctrl+L', parent.loadFile),
            s(':/pix/save_file', QObject.tr(self, 'Save file'), 'Ctrl+S', parent.saveFile),
            s('', '', '', None),
            s(':/pix/selection', QObject.tr(self, 'Selection mode'), 'S', parent.selectionMode),
            s(':/pix/box', QObject.tr(self, 'Box mode'), 'B', parent.boxMode),
            s('', '', '', None),
            s(':/pix/prev_box', QObject.tr(self, 'Select previous box'), 'Shift+Tab', parent.selectPreviousBox),
            s(':/pix/next_box', QObject.tr(self, 'Select next box'), 'Tab', parent.selectNextBox),
            s(':/pix/edit_box', QObject.tr(self, 'Edit box type'), 'E', parent.editBox),
            s(':/pix/zoom_in', QObject.tr(self, 'Zoom in'), '+', parent.zoomIn),
            s(':/pix/zoom_out', QObject.tr(self, 'Zoom out'), '-', parent.zoomOut),
            s('', '', '', None),
            s(':/pix/copy_box', QObject.tr(self, 'Copy box'), 'Ctrl+C', parent.copyBox),
            s(':/pix/cut_box', QObject.tr(self, 'Cut box'), 'Ctrl+X', parent.cutBox),
            s(':/pix/paste_box', QObject.tr(self, 'Paste box'), 'Ctrl+V', parent.pasteBox),
            s('', '', '', None),
            s(':/pix/help', QObject.tr(self, 'Builder help'), 'F1', parent.builderHelp),
            s(':/pix/quit', QObject.tr(self, 'Quit'), 'Ctrl+Q', parent.quitBuilder)]

        actionsList = []
        for item in self.buttons:
            if item.slot == None:
                QtGui.QToolBar.addSeparator(self)
            else:
                action = QtGui.QAction(QtGui.QIcon(item.pixPath), '', self)
                QtGui.QAction.setShortcut(action, item.shortcut)
                QtGui.QAction.setToolTip(action, QString('%1 (%2)').arg(item.tooltip).arg(item.shortcut))
                actionsList.append(action)
                QtGui.QToolBar.addAction(self, action)
                QtGui.QMainWindow.addAction(parent, action)
                QObject.connect(action, SIGNAL("triggered()"), item.slot)
