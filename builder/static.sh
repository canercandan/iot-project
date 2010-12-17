#!/bin/sh

icons='icons_rc.py'
boxEditorUiPy='BoxEditor_ui.py'
progNameUiPy='ProgName_ui.py'

config()
{
    # All icons (.png) become one file (.py)
    echo 'Compiling resources...'
    pyrcc4 resources.qrc -o $icons
    echo $icons 'has been generated.'

    # Xml file (.ui) becomes a python class
    echo 'Compiling ui files...'
    pyuic4 ProgName.ui -o $progNameUiPy
    echo $progNameUiPy 'has been generated'
    pyuic4 BoxEditor.ui -o $boxEditorUiPy
    echo $boxEditorUiPy 'has been generated.'
}

build()
{
    output=`pwd`'/build/dist'

    echo 'o------------------------------------o'
    echo '  Building IotBuilder static binary'
    echo 'o------------------------------------o'

    config

    if [ ! -d build ]
    then
	mkdir build
    fi

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
	echo 'Build first then debpack.'
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
    rm -vf $progNameUiPy
}

case $1 in
    config) config;;
    build) build;;
    clean) clean;;
    debpack) debpack;;
    *) echo 'usage: static config | build | clean | debpack';;
esac
