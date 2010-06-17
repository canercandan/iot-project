#!/bin/sh

if [ $# -ne 1 ]
then
    echo "usage: ./pack.sh <file.py>"
    exit 1
fi

if [ `basename "$1" | cut -d. -f2` != "py" ]
then
    echo "Need python file"
    exit 1
fi

pyFile=`basename "$1"`
project=`echo $1 | awk -F/ '{print $(NF-1)}'`
specFilename=`echo $pyFile | cut -d. -f1`.spec

cd pyinstaller-1.4

echo "o------------------------o"
echo " Making spec in progress"
echo "o------------------------o"

python Makespec.py -o ../$project --onefile "$1"

echo ""
echo "o--------------------o"
echo " Building in progress"
echo "o--------------------o"

python Build.py ../$project/$specFilename

echo ""
echo "o--------------------o"
echo " Sucessful building"
echo "o--------------------o"
echo "Binary path: $project/dist/"
echo "Binary filename: "`echo $pyFile | cut -d. -f1`

exit 0
