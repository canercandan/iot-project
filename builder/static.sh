#!/bin/sh

icons='icons_rc.py'
boxEditorUiPy='BoxEditor_ui.py'

build()
{
    output=`pwd`'/build/dist'

    if [ ! -d build ]
    then
	mkdir build
    fi

    # All icons (.png) become one file (.py)
    echo 'Compiling resources...'
    pyrcc4 resources.qrc -o $icons

    # Xml file (.ui) becomes a python class
    echo 'Compiling ui files...'
    pyuic4 BoxEditor.ui > $boxEditorUiPy

    cd build
    cmake ..
    make

    echo 'o----------------------'
    echo '  Binary is located in '$output
    echo 'o----------------------'
}

debpack()
{
    if [ ! -d build ]
    then
	echo 'Build first then pack.'
	exit 0
    fi

    cd build
    cpack -G DEB
}

clean()
{
    rm -rf build
    echo 'build directory removed'
    rm -vf $icons
    rm -vf $boxEditorUiPy
}

case $1 in
    build) build;;
    clean) clean;;
    debpack) debpack;;
    *) echo 'usage: static build | clean | debpack';;
esac
