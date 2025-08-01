# Day 5: Print Queue

The [problem](https://adventofcode.com/2024/day/5) for this day.

The first part aims to find every valid update in a sequence of updates. Each update has a series of page, and they must follow a set of ordering rules. Then, we need to find the sum of the middle page of each valid update.

The second part consisted in

## How to use

As explained in the [Readme](../../README.md) of the project, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.  

Eg:

- `./install/bin/day_5/print_queue install/share/day_5/data/puzzle_input.txt`

## Solution

The sum of all middle pages from valid updates is 5087. This has been achieved with O(r+p) space complexity, with r being the number of rules and p the total number of pages in all updates. The time complexity is O(p + r*u), where p is the number of pages, r is the number of rules and u is the number of updates.
