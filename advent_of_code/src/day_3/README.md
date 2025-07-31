# Day 3: Mull It Over

The [problem](https://adventofcode.com/2024/day/3) for this day.

The first part aims to sum a series of multiplication hidden in a corrupted memory file. The numbers to multiply are all integers and they should match the pattern "mul(x, y)". Any number of invalid characters can mix with this expression.

The second part aims at identifying special "do()" and "don't()" operations in the memory. Any "mul(x, y)" found after a "don't()" will be ignored, until the next "do()".

## How to use

As explained in the [Readme](../../README.md) of the project, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.

Eg:

- `./install/bin/day_3/mull_over install/share/day_3/data/puzzle_input.txt`

## Solution

The total sum of each mul() operation is 161289189.
When the do() and don't() instructions are considered, the result is 83595109.  
These results were obtained with O(n) time complexity and O(n) space complexity.
