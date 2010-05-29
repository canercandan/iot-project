#!/bin/sh

wget -O pyinstaller-1.4.tar.bz2 -c http://www.pyinstaller.org/static/source/1.4/pyinstaller-1.4.tar.bz2
tar xfj pyinstaller-1.4.tar.bz2
cd pyinstaller-1.4/source/linux
python Make.py
make
cd ../../
python Configure.py
