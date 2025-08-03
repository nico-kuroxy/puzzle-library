# Advent of code

[Advent of code](https://adventofcode.com/2024/about) is an advent calendar of small programming puzzles for a variety of skill levels that can be solved in any programming language.

## How to install

The [build.sh](build.sh) script allows to compile and install all the code of this project. It relies on cmake, so make sure you have at least the version 3.14 installed on your computer. Furthermore, the unit tests are using the GTest suite, so make sure you have it installed as well.

The first step is to make the script executable with `chmod +x build.sh`. Then, just call it from your terminal with `./build.sh` or `bash build.sh` according to what is available on your installation.

Be careful, if you are building on windows with WSL, you might have to change the end-of-line sequence of the script from CRLF to LF. This can be done in Visual Studio Code, for instance. Otherwise, there might be issues with carriage return (\r) characters.

Your built objects should be in the **build** folder, while the executable are in the **install/bin** folder.

It should be noted that for each executable of the advent of code, we need to load a data file within our code. These data file are installed in the **install/share** folder during building.

Furthermore, each header file has been commented following Doxygen documentation style.

## How to use

To execute the program of your choice, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.

Eg:

- `./install/bin/day_1/historian_hysteria install/share/day_1/data/puzzle_input.txt`
- `./install/bin/day_2/red_reports install/share/day_2/data/puzzle_input.txt`
- `./install/bin/day_3/mull_over install/share/day_3/data/puzzle_input.txt`
- `./install/bin/day_4/ceres_search install/share/day_4/data/puzzle_input.txt XMAS MAS`
- `./install/bin/day_5/print_queue install/share/day_5/data/puzzle_input.txt`

## How to test

This project implements a few unit tests through the [GTest](https://google.github.io/googletest/) testing framework.  
The binaries for the unit tests of each day are stored in the **build** folder. To run them, just use `ctest --test-dir build` from the **advent_of_code**  directory.
