bin2hpp
=======

Binary to C++ header file generator

bin2hpp is a command line tool for generating C++ header files of binary
data. The generated header file will contain an array rappresenting the
content of the file.


Alternatives
------------

Advantages over resources
-------------------------

0. Take advantage of compile time optimisation from the compiler
0. No runtime failure loading the resource (failure is at compile time)
0. Portable, works on all systems with all (conformant) compilers
0. Compile time checks on resource can be made (size, patterns, ...)
0. There are no encoding issues, the generated file is an ascii file


Disadvantages over other systems
--------------------------------
0. You need a separate build step
0. It is difficultier to manage resource
0. You loose information, since every file is converted to a binary string, and you need an (unsafe) cast/conversion, to handle the binary file, for example, as an image.
