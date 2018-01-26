# sld2bnd
Solidworks *.sld to *.bnd format converter

# Content

This project contains the `sld2bnd` binary source code that allows to convert
*.sld files into *.bnd files. These files are used in ViSP (https://github.com/lagadic/visp) robot simulator.

# How to build (tested on ubuntu 16.04)

    sudo apt-get install bison
    mkdir build
    cd build
    cmake ..
    make

# How to use

   ./sld2bnd -?

Example

   ./sld2bnd -o bras.bnd../data-sld/bras.sld

