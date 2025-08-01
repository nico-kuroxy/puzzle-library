# Day 4: Ceres Search

The [problem](https://adventofcode.com/2024/day/4) for this day.

The first part aims to find all occurences of a given word ("XMAS") in a crossword grid. This word search allows words to be horizontal, vertical, diagonal, written backwards, or even overlapping other words.

The second part consisted in finding a pattern of words on diagonals crossing each other through their centers.

## How to use

As explained in the [Readme](../../README.md) of the project, just use `./install/bin/day_X/your_executable install/share/day_X/data/some_data.txt`. Make sure to replace **day_X**, **executable** and **some_data** by the proper file/folder names.  

This is the only program which needs extra arguments on the command line. The first one is the word to look for in the crossword, the second is the word to look for with the cross pattern. The pattern word should be of size 3. It could further generalized to any word of odd size, or any word at all given a rule to handle even sized word.

Eg:

- `./install/bin/day_4/ceres_search install/share/day_4/data/puzzle_input.txt XMAS MAS`

## Solution

The word "XMAS" was found 2543 times in the input grid. This has been obtained with O( c\*r) time complexity and 0(c\*r) space complexity, where c, r are respectively the number of columns and rows. The size of the word has no impact on the time complexity, since we hash it on the fly.  
The "MAS" crosses were found 1930 times in the input grid. This has been obtained with O( c\*r) time complexity and 0(c\*r) space complexity.
