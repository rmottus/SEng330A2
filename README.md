# Software Engineering 330 Assignment 2
Repo for SEng 330 Assignment 2 at UVic during the Fall 2015 semester.

## Introduction
The project is created in Visual Studio 2013 Community (with VC++11), and includes the project files to be imported directly into this program. It should support all 32/64-bit Windows systems that can run Visual Studio 2013, but it should be noted that all development and testing was on a Windows 10 64-bit computer.

This solution consists of three projects:
* SEng330A2Lib creates a library of the base functionality for the solution.
* SEng330A2Main creates an executable console application that takes user input to create/save/load/print machines.
* SEng330A2Test creates an executable test application that tests SEng330A2Lib.

Documentation for each part can be found in the SEng330A2/Docs/html/ folder (open index.html). For documentation on the tests see SEng330A2Test.cpp; for the console application see SEng330A2Main.cpp. The library consists of multiple classes and header files, each of which is documented in the above location, with the exception of the protocol buffer classes that were automatically generated.

It uses Google Protocol Buffers 2.6.1 for saving/loading, Google Test 1.7.0 for tests, and Doxygen 1.8.10 to generate documentation.

## Installation
1. Clone this repository locally with Visual Studio and open the solution.
    1. See this page for instructions http://www.malgreve.net/2014/06/17/cloning-getting-code-from-git-repository-to-visual-studio/.
2. Select Build -> Build Solution. By default this will build the project for debugging. If you wish to only build for release, change Debug to Release at the top of the screen.
3. If you wish to run the code from within Visual Studio, you can:
    1. Right click on the project that you wish to run (SEng330A2Main or SEng330A2Test) and select "Set as StartUp Project"
    2. Choose Debug -> Start Without Debugging from the top menu. 
4. You may also run the program manually by going to `<CheckoutDirectory>\SEng330A2\SEng330A2\<Debug_or_Release>\` and running `SEng330A2Main.exe` (or `SEng330A2Test.exe`).
5. To regenerate the protocol buffer files, from within the `<CheckoutDirectoy>\SEng330A2\SEng330A2\protobuf` folder run the command:

    `protoc -I=<CheckoutDirectoy>\SEng330A2\SEng330A2\SEng330A2Lib\ --cpp_out=<CheckoutDirectoy>\SEng330A2\SEng330A2\SEng330A2Lib\ <CheckoutDirectoy>\SEng330A2\SEng330A2\SEng330A2Lib\MachineList.proto`

6. To regenerate documentation, run `deoxygen` or `deoxygen Doxyfile` from `<CheckoutDirectory>\SEng330A2\SEng330A2`. You can also open the `<CheckoutDirectory>\SEng330A2\SEng330A2\Doxyfile` in the Deoxygen GUI and generate it that way.
    1. Doxygen can be download from http://www.stack.nl/~dimitri/doxygen/download.html 

---
Created and maintained by Riley Mottus (V00749270) for SEng 330 at the University of Victoria in Fall 2015.
