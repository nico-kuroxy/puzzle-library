# Test cases

This repository contains the implementation of some test cases.

## How to install

The [build.sh](build.sh) script allows to compile and install all the code of this project. It relies on cmake, so make sure you have at least the version 3.14 installed on your computer. Furthermore, the unit tests are using the GTest suite, so make sure you have it installed as well.

The first step is to make the script executable with `chmod +x build.sh`. Then, just call it from your terminal with `./build.sh` or `bash build.sh` according to what is available on your installation.

Be careful, if you are building on windows with WSL, you might have to change the end-of-line sequence of the script from CRLF to LF. This can be done in Visual Studio Code, for instance. Otherwise, there might be issues with carriage return (\r) characters.

Your built objects should be in the **build** folder, while the executables or libraries are in the **install** folder.

Furthermore, each header file has been commented following Doxygen documentation style.

## How to test

This project implements a few unit tests through the [GTest](https://google.github.io/googletest/) testing framework.  
The binaries for the unit tests of each functions are stored in the **build** folder. To run them, just use `ctest --test-dir build` from the **test_case**  directory.
