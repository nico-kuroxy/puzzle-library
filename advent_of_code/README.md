# Advent of code

[Advent of code](https://adventofcode.com/2024/about) is an advent calendar of small programming puzzles for a variety of skill levels that can be solved in any programming language.

## How to install

The [build.sh](build.sh) script allows to compile and install all the code of this project. It relies on cmake, so make sure you have at least the version 3.14 installed on your computer.

The first step is to make the script executable with `chmod +x build.sh`. Then, just call it from your terminal with `./build.sh`.  

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
