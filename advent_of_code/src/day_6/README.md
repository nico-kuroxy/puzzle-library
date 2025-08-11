# Day 6: Guard Gallivant

The [problem](https://adventofcode.com/2024/day/6) for this day.

The first part aims to

The second part consisted in 

We are making the assumption that 

## How to use

As explained in the [Readme](../../README.md#how-to-use) of the project, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.  

Eg:

- `./install/bin/day_6/guard_gallivant install/share/day_6/data/puzzle_input.txt`

## How to test

As explained in the [Readme](../../README.md/#how-to-test) of the project, just use `ctest --test-dir build` to run all the GTest test case defined for this project.

## Solution

The guard will visit 5531 distinct positions on the map. This has been achieved with a O(n) time complexity (if we are not considering the exploration of the map which can be endless) and O(n) space complexity (with n the size of the map / the number of cell).
