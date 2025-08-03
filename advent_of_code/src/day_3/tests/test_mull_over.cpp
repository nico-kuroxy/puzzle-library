/**
 * @file test_mull_over.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the test cases of the Mull Over problem proposed in Day 3 of the Advent of Code.
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
#include <day_3/mull_over.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> TEST CASES

//> Test cases for the loadDataFromFile() function.
/**
 * @brief Unit test for the MullOver::loadDataFromFile method.
 *        This test verifies that a valid file is read and parsed correctly.
 */
TEST(LoadDataFromFile, ValidInput) {
    // Instantiate the test class.
    MullOver test("");
    // Initialize the test input.
    std::string memory;
    // Create a temporary file with valid data.
    const std::string filename = "test_input_valid_day3.txt";
    std::ofstream out(filename);
    out << "mul(2,3)\nmul(4,5)\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, memory);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // Check that data was parsed correctly.
    EXPECT_NE(memory.find("mul(2,3)"), std::string::npos);
    EXPECT_NE(memory.find("mul(4,5)"), std::string::npos);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the MullOver::loadDataFromFile method.
 *        This test verifies the case where the input file does not exist.
 */
TEST(LoadDataFromFile, FileNotFound) {
    // Instantiate the test class.
    MullOver test("");
    // Initialize the test input.
    std::string memory;
    // Attempt to load from a non-existent file.
    int result = test.loadDataFromFile("nonexistent_file.txt", memory);
    // The return code should be 1 (file could not be opened).
    EXPECT_EQ(result, 1);
    // The memory string should remain empty.
    EXPECT_TRUE(memory.empty());
}

//> Test cases for the multiplyMemory() function.
/**
 * @brief Unit test for the MullOver::multiplyMemory method.
 *        This test verifies the basic multiplication logic.
 */
TEST(MultiplyMemory, BasicMultiplication) {
    // Instantiate the test class.
    MullOver test("");
    // Initialize the test input.
    std::string memory = "mul(2,3)mul(4,5)";
    int result = -1, instructions = -1;
    bool mul_enabled = true;
    // Execute the function.
    int status = test.multiplyMemory(memory, result, instructions, mul_enabled);
    // Should return 0 (success).
    EXPECT_EQ(status, 0);
    // Expected result is 2*3 + 4*5 = 6 + 20 = 26.
    EXPECT_EQ(result, 26);
    // All multiplications counted.
    EXPECT_EQ(instructions, 26);
}
/**
 * @brief Unit test for the MullOver::multiplyMemory method.
 *        This test verifies that don't() disables multiplication.
 */
TEST(MultiplyMemory, MultiplicationDisabled) {
    // Instantiate the test class.
    MullOver test("");
    // Initialize the test input.
    std::string memory = "mul(1,1)don't()mul(10,10)";
    int result = -1, instructions = -1;
    bool mul_enabled = true;
    // Execute the function.
    int status = test.multiplyMemory(memory, result, instructions, mul_enabled);
    // Should return 0 (success).
    EXPECT_EQ(status, 0);
    // Total result includes both multiplications.
    EXPECT_EQ(result, 1 + 100);
    // Instructions should only include the first mul.
    EXPECT_EQ(instructions, 1);
}
/**
 * @brief Unit test for the MullOver::multiplyMemory method.
 *        This test verifies that do() re-enables multiplication.
 */
TEST(MultiplyMemory, ReenableMultiplication) {
    // Instantiate the test class.
    MullOver test("");
    // Initialize the test input.
    std::string memory = "mul(2,2)don't()mul(3,3)do()mul(4,4)";
    int result = -1, instructions = -1;
    bool mul_enabled = true;
    // Execute the function.
    int status = test.multiplyMemory(memory, result, instructions, mul_enabled);
    // Should return 0 (success).
    EXPECT_EQ(status, 0);
    // Total result: 4 + 9 + 16 = 29.
    EXPECT_EQ(result, 29);
    // Instructions counted only when enabled: 4 + 16 = 20.
    EXPECT_EQ(instructions, 20);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


