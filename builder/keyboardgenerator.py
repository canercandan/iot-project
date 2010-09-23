import sys

from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4.QtXml import *

def generate_keyboard(topLeft_x, topLeft_y, bottomRight_x, bottomRight_y, filename = "keyboard.xml", nb_col = 10, nb_line = 4, my_keymap = "AZERTYUIOPQSDFGHJKLMWXCVBN 0123456789"):
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
    caseSizey = sizey // nb_line
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

        my_file.write("\t" + '<box type="2" x="' + str(x) + '" y="' + str(y) + '" height="' + str(caseSizey) + '" width="' + str(caseSizex) + '">' + "\n")
        my_file.write("\t" + "\t" + '<action id="ExecMenu">' + "\n")
        my_file.write("\t" + "\t" + "\t" + '<action id="Keyboard" press="' + c + '" />' + "\n")
        my_file.write("\t" + "\t" + '</action>' + "\n")
        my_file.write("\t" + '<style opacity="1" text="' + c + '"/>' + "\n")
        my_file.write("\t" + '</box>' + "\n")
        col += 1

    if col >= nb_col:
        col = 0
        line += 1
    if line >= nb_line:
        print "keymap too big"
        return
    my_file.write("\t" + '<box type="2" x="' + str(x) + '" y="' + str(y) + '" height="' + str(caseSizey) + '" width="' + str(caseSizex) + '">' + "\n")
    my_file.write("\t" + "\t" + '<action id="ExecMenu">' + "\n")
    my_file.write("\t" + "\t" + "\t" + '<action id="Cancel"/>' + "\n")
    my_file.write("\t" + "\t" + '</action>' + "\n")
    my_file.write("\t" + '<style opacity="1" text="Back" fr-text="Retour" imagePath=":images/menu/cancel.png" rounded="true"/>' + "\n" + "\t" + '</box>' + "\n")

    my_file.write('</menu>' + "\n")
    my_file.close()


generate_keyboard(0, 0, 640, 300, "640_300_azerty.xml")
