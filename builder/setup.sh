#!/bin/sh

install()
{
    pyiPath="$HOME/pyinstaller-1.4"

    if [ ! -d pyiPath ]
    then
	echo "PyInstaller is already installed in $pyiPath"
	exit 0
    fi

    cd $HOME

    wget -c http://www.pyinstaller.org/static/source/1.4/pyinstaller-1.4.tar.bz2 \
	-O /tmp/pyinstaller-1.4.tar.bz2
    tar xfj /tmp/pyinstaller-1.4.tar.bz2

    cd pyinstaller-1.4/source/linux
    python Make.py
    make
    cd ../../
    python Configure.py
}

install
