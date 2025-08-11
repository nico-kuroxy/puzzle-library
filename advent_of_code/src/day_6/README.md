# Day 6: Guard Gallivant

The [problem](https://adventofcode.com/2024/day/6) for this day.

The first part aims to find the number of distinct positions that a guard will occupy on a grid map before leaving it. This guard will move according to a pre-established pattern: straight when there is no obstacle, rotate 90degrees when facing one.

The second part consisted in [TODO].

We are making the assumption that the maps are wel-formatted, and the guard can go to any space that is not a "#". If there were multiple guards, they could occupy the same cell...

## How to use

As explained in the [Readme](../../README.md#how-to-use) of the project, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.  

Eg:

- `./install/bin/day_6/guard_gallivant install/share/day_6/data/puzzle_input.txt`

## How to test

As explained in the [Readme](../../README.md/#how-to-test) of the project, just use `ctest --test-dir build` to run all the GTest test case defined for this project.

## Solution

The guard will visit **5531** distinct positions on the map. This has been achieved with a O(n) time complexity (if we are not considering the exploration of the map which can be endless) and O(n) space complexity (with n the size of the map / the number of cell).
