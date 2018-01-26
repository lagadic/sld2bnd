# sld2bnd
Solidworks `*.sld` to `*.bnd` format converter

# Content

This project contains the `sld2bnd` binary source code that allows to convert
`*.sld` files into `*.bnd` files. These files are used in ViSP (https://github.com/lagadic/visp) robot simulator.

This project was tested on Ubuntu 16.04 and OsX.
The only external dependency is `bison`.

# How to build

    sudo apt-get install bison
    mkdir build
    cd build
    cmake ..
    make

# How to use

    ./sld2bnd -?

Example

    ./sld2bnd -o bras.bnd../data-sld/bras.sld

