# Day 2: Red-Nosed Reports

The [problem](https://adventofcode.com/2024/day/2) for this day.

The first part aims to determine which reports provided as input are safe. This is the case if the levels are either all increasing or all decreasing and if any two adjacent levels differ by at least one and at most three. The levels recorded for each report are all strictly positive in the example, but they are not unique.

The second part aims to introduce a damping factor. The idea is to consider that a report is safe if removing one level from it is enough to meet all the criteria.

## How to use

As explained in the [Readme](../../README.md#how-to-use) of the project, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.

Eg:

- `./install/bin/day_2/red_reports install/share/day_2/data/puzzle_input.txt`

## How to test

As explained in the [Readme](../../README.md/#how-to-test) of the project, just use `ctest --test-dir build` to run all the GTest test case defined for this project.

## Solution

The total number of safe reports is **218**. This has been achieved with O(n) time complexity and O(n) space complexity.  
Now, if we consider the damping factor, we obtain **290** safe reports. This has been achieved with O(n*k) time complexity and O(n) space complexity. It should be noted that I am not really satisfied with the time complexity, I think there should be a faster way to process the reports in one go, instead of brute-forcing it. But I didn't have the time to figure out all the edge-cases.
