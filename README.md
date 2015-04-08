PrefLib
====

This project provides PREF's core source code in a lightweight static library.
This library will be part of PREF 2.x series.

Basically, this library is a rewrite of PREF 1.x core and provides a clean 
Lua/Capstone core for Data/Format analysis and Disassembling.

Everyone can write a graphical front-end for this library in order to provide 
a PREF version with its favorite GUI Toolkit and Operating System.

Library's Structure
-----
The library's is composed by C++ namespaces in order to provide 
the cleanest possible implementation:

- Format Parser Engine
- Binary Charts (Histogram, Entropy and Byte Class based)
- Binary Maps (DotPlot, BinaryMap, and Byte as Pixel)
- Support Library for common data operations
- Platform Independent I/O classes
- Type Independent data types (type/DataValue is basically a Variant)
- User Defined Exporters
- Disassembler Engine (Custom or Capstone based disassembler, under development)

Dependencies
-----
- Lua >= 5.2
- Capstone Engine