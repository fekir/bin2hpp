bin2hpp
=======

Binary to C++ header file generator

bin2hpp is a command line tool for generating C++ header files of binary
data. The generated header file will contain an array rappresenting the
content of the file.

```
Usage: bin2hpp [options] -in [input files] -names [optional names] -out [optional output files]

 Options:
 ========
    -ns= <namespace>
        for specifying namespace, use -ns="" for removing the namespace. Default namespace is "resource"
    -pragma
        for using a pragma instead of an include guard
    -std= <standard-id>
        for specifying language and/or language revision, for example -std=c++11.
        Valid revisions for c++ are:  c++, c++98, c++03, c++11, c++14, c++17
        Valid revisions for c are:    c, c89, c99, c11
        Valid revisions for java are: j, j1.3, j1.4, j1.5, j1.6, j1.7j1.8, j1.9
    -const= <const-id>
        for specifying const id of array and size.
    -constsize= <const-id>.
        for specifying const id of size.
    -constarr= <const-id>
        for specifying const id of array.
    -stdarr= <true/false>
        (only c++) for specifying if using std::array or a plain old and unsafe array.
    -in <list-input-files>
         list of input files, separated by space.
    -out <list-output-files>
        list of output files, separated by space.
    -names <list-variable-names>
        list of variable names, separated by space.
```

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
