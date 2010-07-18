#!/bin/sh

build()
{
    output=`pwd`'/build/dist'

    if [ ! -d build ]
    then
	mkdir build
    fi

    # All icons (.png) become one file (.py)
    pyrcc4 resources.qrc -o icons_rc.py

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
    rm -r build
}

case $1 in
    build) build;;
    clean) clean;;
    debpack) debpack;;
    *) echo 'usage: static build | clean | debpack';;
esac
