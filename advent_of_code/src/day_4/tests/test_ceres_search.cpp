/**
 * @file test_ceres_search.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the test cases of the Ceres Search problem proposed in Day 4 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
//> Custom-made libraries
#include <day_4/ceres_search.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> TEST CASES

//> Test cases for the loadDataFromFile() function.
/**
 * @brief Unit test for the CeresSearch::loadDataFromFile method.
 *        This test verifies the loading of a properly formatted grid file.
 */
TEST(LoadDataFromFile, ValidGrid) {
    // Instantiate the test class.
    CeresSearch test("");
    // Initialize the input variables.
    std::vector<std::vector<char>> grid;
    // Create a test input file.
    const std::string filename = "test_input_valid_day4.txt";
    std::ofstream out(filename);
    out << "ABC\nDEF\nGHI\n";
    out.close();
    // Attempt to load the file.
    int result = test.loadDataFromFile(filename, grid);
    // Check result. We should not have any error code.
    EXPECT_EQ(result, 0);
    // Check content.
    ASSERT_EQ(grid.size(), 3);
    EXPECT_EQ(grid[0], std::vector<char>({'A','B','C'}));
    EXPECT_EQ(grid[1], std::vector<char>({'D','E','F'}));
    EXPECT_EQ(grid[2], std::vector<char>({'G','H','I'}));
    // Clean up.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the CeresSearch::loadDataFromFile method.
 *        This test verifies the behavior when the file does not exist.
 */
TEST(LoadDataFromFile, FileNotFound) {
    // Instantiate the test class.
    CeresSearch test("");
    // Initialize the input variables.
    std::vector<std::vector<char>> grid;
    // Load from nonexistent file.
    int result = test.loadDataFromFile("nonexistent.txt", grid);
    // Check the result, we should have error code 1.
    EXPECT_EQ(result, 1);
}

//> Test cases for the countWords() function.
/**
 * @brief Unit test for the CeresSearch::countWords method.
 *        This test verifies detection of a simple word horizontally.
 */
TEST(CountWords, HorizontalWordFound) {
    // Instantiate the test class.
    CeresSearch test("");
    // Initialize the input variables.
    std::vector<std::vector<char>> grid = {
        {'H', 'E', 'L', 'L', 'O'},
        {'A', 'B', 'C', 'D', 'E'},
        {'X', 'Y', 'Z', 'T', 'S'}
    };
    std::vector<std::pair<int, int>> directions = {{0, 1}};
    int nb_found = 0;
    std::string word = "HELLO";
    uint64_t BASE = 257;
    uint64_t MOD = 1000000007;
    // Call function.
    int result = test.countWords(grid, directions, word, nb_found, BASE, MOD);
    // Check result. We should not have any returned error code.
    EXPECT_EQ(result, 0);
    // And we should find the word exactly once.
    EXPECT_EQ(nb_found, 1);
}
/**
 * @brief Unit test for the CeresSearch::countWords method.
 *        This test verifies that malformed grids return an error.
 */
TEST(CountWords, MalformedGrid) {
    // Instantiate the test class.
    CeresSearch test("");
    // Initialize the input variables.
    std::vector<std::vector<char>> grid = {
        {'A', 'B'},
        {'C'},
        {'D', 'E'}
    };
    std::vector<std::pair<int, int>> directions = {{0, 1}};
    int nb_found = 0;
    std::string word = "AB";
    uint64_t BASE = 257;
    uint64_t MOD = 1000000007;
    // Call function.
    int result = test.countWords(grid, directions, word, nb_found, BASE, MOD);
    // Check the result. We should have the error code 1 returning.
    EXPECT_EQ(result, 1);
}

//> Test cases for the countPattern() function.
/**
 * @brief Unit test for the CeresSearch::countPattern method.
 *        This test verifies the detection of cross patterns.
 */
TEST(CountPattern, CrossPatternDetected) {
    // Instantiate the test class.
    CeresSearch test("");
    // Initialize input variables.
    std::vector<std::vector<char>> grid = {
        {'X', 'A', 'X'},
        {'A', 'M', 'S'},
        {'X', 'A', 'X'}
    };
    std::string pattern = "XMX";
    std::vector<std::pair<int, int>> dir1 = {{-1, -1}, {0, 0}, {1, 1}};
    std::vector<std::pair<int, int>> dir2 = {{-1, 1}, {0, 0}, {1, -1}};
    int nb_xmas_found = 0;
    // Call function.
    int result = test.countPattern(grid, dir1, dir2, nb_xmas_found, pattern);
    // Check the result. It should not return any error code.
    EXPECT_EQ(result, 0);
    // And we should have found 1 pattern.
    EXPECT_EQ(nb_xmas_found, 1);
}
/**
 * @brief Unit test for the CeresSearch::countPattern method.
 *        This test verifies handling of invalid pattern size.
 */
TEST(CountPattern, InvalidPatternSize) {
    // Instantiate the test class.
    CeresSearch test("");
    // Initialize input variables.
    std::vector<std::vector<char>> grid = {{'A'}};
    std::string pattern = "LONG";
    std::vector<std::pair<int, int>> dir;
    int nb_xmas_found = 0;
    // Call the function.
    int result = test.countPattern(grid, dir, dir, nb_xmas_found, pattern);
    // Check the result, it should return the error code 1.
    EXPECT_EQ(result, 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


