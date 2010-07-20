pyrcc4 resources.qrc -o icons_rc.py
call pyuic4.bat BoxEditor.ui -o BoxEditor_ui.py

mkdir build
cd build

cmake -G "MinGW Makefiles" ..
mingw32-make

cd ..
