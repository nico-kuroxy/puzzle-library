# Day 4: Ceres Search

The [problem](https://adventofcode.com/2024/day/4) for this day.

The first part aims to find all occurences of a given word ("XMAS") in a crossword grid. This word search allows words to be horizontal, vertical, diagonal, written backwards, or even overlapping other words.

The second part consisted in finding a pattern of words on diagonals crossing each other through their centers.

## How to install

## How to use

## Solution

The word "XMAS" was found 2543 times in the input grid. This has been obtained with O( c\*r) time complexity and 0(c\*r) space complexity, where c, r are respectively the number of columns and rows. The size of the word has no impact on the time complexity, since we hash it on the fly.  
The "MAS" crosses were found 1930 times in the input grid. This has been obtained with O( c\*r) time complexity and 0(c\*r) space complexity.
