Hardware Interface Control framework
====================================
A Framework for controlling hardware systems via multiple interfaces
e.g. web, gui, command line

Building
========
hic uses the multi-platform build system "cmake".
Create a directory for the build, and point cmake to the top level src directory
(the first one with a CMakeLists.txt file in it).

e.g. on a Unix system you can use

mkdir build
cd build
cmake ../src
make
