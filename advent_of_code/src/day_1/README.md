# Day 1: Historian Hysteria

The [problem](https://adventofcode.com/2024/day/1) for this day.

The first part aims to determine the total distance between two lists of positive integers (or IDs) of equal sizes. Even though the provided example contains duplicate IDs, the problem states that they should be unique (as it is the case in the puzzle input).

The second parts aims to determine the similarity between those two lists.

## How to use

As explained in the [Readme](../../README.md#how-to-use) of the project, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.

Eg:

- `./install/bin/day_1/historian_hysteria install/share/day_1/data/puzzle_input.txt`

## How to test

As explained in the [Readme](../../README.md/#how-to-test) of the project, just use `ctest --test-dir build` to run all the GTest test case defined for this project.

## Solution

The distance between the left and right lists is **2057374**. This has been obtained with O(n log n) time complexity and 0(1) space complexity. We could have achieved O(n) time complexity with a count sort algorithm but this would have required a much higher space complexity (O(w), with w being the value of the highest number in the list).  
The similarity between them is **23177084**. This has been obtained with O(n) time complexity and O(n) space complexity.
