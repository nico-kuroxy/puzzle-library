/**
 * @file ceres_search.hpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the header of the Ceres Search problem proposed in Day 4 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

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
/**
 * @class CeresSearch
 * @brief A class to process the Advent of Code Day 4 problem.
 *
 * Inherits from BaseAdventDay. This class loads a character grid, computes hashes,
 * searches for words or patterns, and tracks occurrences using custom logic.
 */

 public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> CONSTRUCTORS
    /**
     * @brief Constructor of the class. Declared as explicit to prevent ambiguous instantiation.
     * @param _filename Path to the input file.
     */
    explicit CeresSearch(std::string _filename);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> DESTRUCTORS
    /**
     * @brief Destructor of the class.
     */
    ~CeresSearch();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /**
     * @brief Declare a run function to comply with the base class.
     * @return 0 on success, non-zero on failure.
     */
    int run();
    /**
     * @brief Run the code to search for a word and a pattern.
     * @param _word The target word to find.
     * @param _pattern The pattern to match (e.g., "XMAS").
     * @return 0 on success, non-zero on error.
     */
    int run(std::string _word, std::string _pattern);
    /**
     * @brief Load data from a text file and fill the character grid.
     * @details
     *   - Temporal complexity: O(n), where n is the number of characters in the grid.
     *   - Space complexity: O(n)
     * @param _fn Input file path.
     * @param _grid Output 2D grid of characters.
     * @return 0 on success, non-zero on failure.
     */
    int loadDataFromFile(const std::string& _fn, std::vector<std::vector<char>>& _grid);

    /**
     * @brief Count occurrences of a word in all directions.
     * @details
     *   - Temporal complexity: O(n), where n is the number of grid characters.
     *   - Space complexity: O(1)
     * @param _grid Input character grid.
     * @param directions_ List of directional offsets to apply.
     * @param _word Word to search for.
     * @param _nb_found Output: number of matches found.
     * @param _BASE Multiplier base for hashing.
     * @param _MOD Modulo for bounded hashing.
     * @return 0 on success, non-zero on failure.
     */
    int countWords(
         const std::vector<std::vector<char>>& _grid, const std::vector<std::pair<int, int>>& directions_,
            const std::string& _word, int& _nb_found, const uint64_t& _BASE, const uint64_t& _MOD);
    /**
     * @brief Compute the polynomial rolling hash of a string.
     * @details
     *   - Temporal complexity: O(w), where w is the size of the word.
     *   - Space complexity: O(1)
     * @param _word Input string to hash.
     * @param _BASE Hash base multiplier.
     * @param _MOD Modulo value.
     * @return Computed hash value.
     */
    uint64_t compute_hash(const std::string& _word, const uint64_t& _BASE, const uint64_t& _MOD);
    /**
     * @brief Count the number of XMAS patterns in the grid.
     * @details
     *   - Temporal complexity: O(n), where n is the number of grid characters.
     *   - Space complexity: O(w), where w is the pattern size.
     * @param _grid The character grid.
     * @param _dir_branch_1 First branch of pattern (e.g., diagonal).
     * @param _dir_branch_2 Second branch of pattern.
     * @param _nb_xmas_found Output: number of found patterns.
     * @param _pattern Pattern string to match.
     * @return 0 on success, non-zero on failure.
     */
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
    /**
     * @brief The crossword grid, represented as a 2D vector of characters.
     */
    std::vector<std::vector<char>> grid_;
    /**
     * @brief Number of found words in the grid.
     */
    int nb_found_;
    /**
     * @brief Number of XMAS patterns found in the grid.
     */
    int nb_xmas_found_;
    //> FIXED / They cannot change during runtime. Declared as const.
    /**
     * @brief Define 8 directions: right, down-right, down, down-left, left, up-left, up, up-right.
     */
    const std::vector<std::pair<int, int>> directions_ = {
         {0, 1},   {1, 1},   {1, 0},   {1, -1},
         {0, -1},  {-1, -1}, {-1, 0},  {-1, 1}
    };
    /**
     * @brief First diagonal for the pattern search.
     */
    const std::vector<std::pair<int, int>> dir_branch_1_ = {{-1, -1}, {0, 0}, {1, 1}};
    /**
     * @brief Second diagonal for the pattern search.
     */
    const std::vector<std::pair<int, int>> dir_branch_2_ = {{1, -1}, {0, 0}, {-1, 1}};
    /**
     * @brief The multiplier base used in the hash function.
     */
    const uint64_t BASE = 257;
    /**
     * @brief The modulus for keeping hashes within a bounded range.
     */
    const uint64_t MOD = 1000000007;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _DAY_4_CERES_SEARCH_HPP_
