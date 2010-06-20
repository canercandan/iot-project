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

import sys

import PyQt4
from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *

import builder
from builder import *

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    builder = BuilderWidget()
    builder.setWindowOpacity(0.4)                                # transparence
    builder.setWindowFlags(QtCore.Qt.FramelessWindowHint)        # barre bleu
    builder.show()                                               # fullscreen
    app.exec_()                                                  # main loop
