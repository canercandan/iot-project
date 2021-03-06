import sys

from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4.QtXml import *

#KEYMAP = "AZERTYUIOPQSDFGHJKLMWXCVBN .?!0123456789@()[]{}:;,"
KEYMAP = "AZERTYUIOPQSDFGHJKLMWXCVBN 0123456789"

def generate_keyboard(topLeft_x, topLeft_y, bottomRight_x, bottomRight_y, filename = "keyboard.xml", nb_col = 10, nb_line = 5, my_keymap = KEYMAP, decal = 8):
    """i generate keyboards with a lot of options !"""
    print """
    ***************
      generating
    ***************
    """
    my_file = open(filename, 'w+')
    my_file.write('<?xml version="1.0" encoding="utf-8"?>' + "\n" + '<!DOCTYPE XmlBox>' + "\n")
    my_file.write('<menu id="Keyboard">' + "\n")
    sizex = bottomRight_x - topLeft_x
    sizey = bottomRight_y - topLeft_y
    caseSizex = sizex // nb_col
    caseSizey = sizey // (nb_line + 1)
    col = 0
    line = 0
    x = 0
    y = 0
    for c in my_keymap:
        if col >= nb_col:
            col = 0
            line += 1
        if line >= nb_line:
            print "keymap too big"
            return
        x = topLeft_x + col * caseSizex
        y = topLeft_y + line * caseSizey

        my_file.write("\t" + '<box type="2" x="' + str(x) + '" y="' + str(y) + '" height="' + str(caseSizey - decal) + '" width="' + str(caseSizex - decal) + '">' + "\n")
        my_file.write("\t" + "\t" + '<action id="ExecMenu">' + "\n")
        my_file.write("\t" + "\t" + "\t" + '<action id="Keyboard" press="' + c + '" />' + "\n")
        my_file.write("\t" + "\t" + '</action>' + "\n")
        my_file.write("\t" + '<style opacity="1" rounded="true" text="' + c + '"/>' + "\n")
        my_file.write("\t" + '</box>' + "\n")
        col += 1

    col = nb_col // 2
    line += 1
    x = topLeft_x + col * caseSizex
    y = topLeft_y + line * caseSizey

    my_file.write("\t" + '<box type="2" x="' + str(x) + '" y="' + str(y) + '" height="' + str(caseSizey - decal) + '" width="' + str(caseSizex - decal) + '">' + "\n")
    my_file.write("\t" + "\t" + '<action id="ExecMenu">' + "\n")
    my_file.write("\t" + "\t" + "\t" + '<action id="Cancel"/>' + "\n")
    my_file.write("\t" + "\t" + '</action>' + "\n")
    my_file.write("\t" + '<style opacity="1" text=" " fr-text=" " imagePath=":images/menu/cancel.png" rounded="true"/>' + "\n" + "\t" + '</box>' + "\n")

    my_file.write('</menu>' + "\n")
    my_file.close()


generate_keyboard(0, 0, 640, 380, "640_300_azerty.xml")
