/**********************************************************************************************************************/
//   author: nicolas.erbetti.k@gmail.com
//   brief: This file defines the header of the Ceres Search problem proposed in the day 4 of the advent of code.
//   copyright: © 2025 Nicolas Erbetti.
/**********************************************************************************************************************/

#ifndef _DAY_4_CERES_SEARCH_HPP_
#define _DAY_4_CERES_SEARCH_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> DEPENDENCIES
//> C/C++ libraries
#include <cstdint>
#include <string>
#include <vector>
//> Custom-made libraries
#include <library/base_advent_day.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> GLOBAL VARIABLES
//> ATOMIC VARIABLES
//> OTHERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> CLASS DECLARATION
class CeresSearch : public BaseAdventDay {
/* A class to process the problem of day 4. */

 public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> CONSTRUCTORS
    /* Constructor of the class. Declared as explicit to prevent ambiguous instanciation. */
    explicit CeresSearch(std::string _filename);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> DESTRUCTORS
    /* Destructor of the class. */
    ~CeresSearch();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /* Declare a run function to comply with the base class. */
    int run();
    /* Run the code to process the input list. */
    int run(std::string _word, std::string _pattern);
    /* Load data from a text file and fill the vectors with the left and right ids.
       Temporal complexity: O(n), where n is the number of characters in the grid.
       Space complexity: O(n). */
    int loadDataFromFile(const std::string& _fn, std::vector<std::vector<char>>& _grid);
    /* Count the words in the grid.
       Temporal complexity: O(n), where n is the number of characters in the grid.
       Space complexity: O(1), where w is the size of the word. */
    int countWords(
         const std::vector<std::vector<char>>& _grid, const std::vector<std::pair<int, int>>& directions_,
            const std::string& _word, int& _nb_found, const uint64_t& _BASE, const uint64_t& _MOD);
    /* Compute the hash of a string using a polynomial rolling hash function.
       Temporal complexity: O(w), where w is the size of the word.
       Space complexity: O(1). */
    uint64_t compute_hash(const std::string& _word, const uint64_t& _BASE, const uint64_t& _MOD);
    /* Count the number of XMAS patterns in the grid.
       Temporal complexity: O(n), where n is the number of characters in the grid.
       Space complexity: O(w), where w is the size of the word. */
    int countPattern(const std::vector<std::vector<char>>& _grid, const std::vector<std::pair<int, int>>& _dir_branch_1,
       const std::vector<std::pair<int, int>>& _dir_branch_2, int& _nb_xmas_found, std::string _pattern);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> ACCESSORS
    //> GETTERS
    //> SETTERS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> GENERAL ATTRIBUTES
    //> DYNAMIC / They can change during runtime.
    /* The crossword grid, which is a vector of vectors of characters. */
    std::vector<std::vector<char>> grid_;
    // Number of found words in the grid. */
    int nb_found_;
    // Number of XMAS patterns found in the grid.
    int nb_xmas_found_;
    //> FIXED / They cannot change during runtime. Declared as const.
    /* Define 8 directions: right, down-right, down, down-left, left, up-left, up, up-right */
    const std::vector<std::pair<int, int>> directions_ = {
         {0, 1},   {1, 1},   {1, 0},   {1, -1},
         {0, -1},  {-1, -1}, {-1, 0},  {-1, 1}
    };
    /* First diagonal for the pattern search. */
    const std::vector<std::pair<int, int>> dir_branch_1_ = {{-1, -1}, {0, 0}, {1, 1}};
    /* Second diagonal for the pattern search. */
    const std::vector<std::pair<int, int>> dir_branch_2_ = {{1, -1}, {0, 0}, {-1, 1}};
    /* The multiplier base used in the hash function. */
    const uint64_t BASE = 257;
    /* The modulus for keeping hashes within a bounded range. */
    const uint64_t MOD = 1000000007;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _DAY_4_CERES_SEARCH_HPP_
