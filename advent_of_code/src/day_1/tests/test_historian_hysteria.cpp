/**
 * @file test_historian_hysteria.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the test cases of the Historian Hysteria problem proposed in Day 1 of the Advent of Code.
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
#include <day_1/historian_hysteria.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> TEST CASES

//> Test cases for the loadDataFromFile() function.
/**
 * @brief Unit test for the HistorianHysteria::loadDataFromFile method.
 *        This test verifies that a correctly formatted file is loaded properly.
 */
TEST(LoadDataFromFile, ValidInput) {
    // Instantiate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left, right;
    // Create a temporary file with valid data.
    const std::string filename = "test_input_valid.txt";
    std::ofstream out(filename);
    out << "1 2\n3 4\n5 6\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, left, right);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The left and right vectors should be populated correctly.
    EXPECT_EQ(left, std::vector<int>({1, 3, 5}));
    EXPECT_EQ(right, std::vector<int>({2, 4, 6}));
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the HistorianHysteria::loadDataFromFile method.
 *        This test verifies the case where the input file does not exist.
 */
TEST(LoadDataFromFile, FileNotFound) {
    // Instantiate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left, right;
    // Attempt to load from a non-existent file.
    int result = test.loadDataFromFile("nonexistent_file.txt", left, right);
    // The return code should be 1 (file could not be opened).
    EXPECT_EQ(result, 1);
}
/**
 * @brief Unit test for the HistorianHysteria::loadDataFromFile method.
 *        This test verifies the case where a line contains extra data.
 */
TEST(LoadDataFromFile, ExtraDataInLine) {
    // Instantiate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left, right;
    // Create a temporary file with a line that includes more than two fields.
    const std::string filename = "test_input_extra.txt";
    std::ofstream out(filename);
    out << "1 2 3\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, left, right);
    // The return code should be 2 (extra data found).
    EXPECT_EQ(result, 2);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the HistorianHysteria::loadDataFromFile method.
 *        This test verifies the case where a line contains negative values.
 */
TEST(LoadDataFromFile, NegativeValues) {
    // Instantiate the test class.
    HistorianHysteria test("");
    // Initialize test input.
    std::vector<int> left, right;
    // Create a temporary file with negative input.
    const std::string filename = "test_input_negative.txt";
    std::ofstream out(filename);
    out << "-1 2\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, left, right);
    // The return code should be 3 (invalid negative values).
    EXPECT_EQ(result, 3);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the HistorianHysteria::loadDataFromFile method.
 *        This test verifies the case where a line is improperly formatted.
 */
TEST(LoadDataFromFile, InvalidFormat) {
    // Instantiate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left, right;
    // Create a temporary file with an invalid line format.
    const std::string filename = "test_input_invalid.txt";
    std::ofstream out(filename);
    out << "invalid line\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, left, right);
    // The return code should be 4 (line could not be parsed correctly).
    EXPECT_EQ(result, 4);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}

//> Test cases for the computeDistance() function.
/**
 * @brief Unit test for the HistorianHysteria::computeDistance method.
 *        This test verifies the basic functionality of the computeDistance function.
 */
TEST(ComputeDistance, BasicCase) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, 2, 3};
    std::vector<int> right{4, 5, 6};
    int distance = 0;
    // In this case, the return code should be 0 (since no error has been detected).
    EXPECT_EQ(test.computeDistance(left, right, distance), 0);
    // Then, the actual measured distance should be 9 (|1-4| + |2-5| + |3-6| = 3+3+3=9)
    EXPECT_EQ(distance, 9);
}
/**
 * @brief Unit test for the HistorianHysteria::computeDistance method.
 *        This test verifies the case where the input vectors have different sizes.
 */
TEST(ComputeDistance, DifferentSizes) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, 2};
    std::vector<int> right{1, 2, 3};
    int distance = 0;
    // In this case, the return code should be 1 (since both side have different sizes).
    EXPECT_EQ(test.computeDistance(left, right, distance), 1);
}
/**
 * @brief Unit test for the HistorianHysteria::computeDistance method.
 *        This test verifies the case where there are negative values in the input.
 */
TEST(ComputeDistance, NegativeValues) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, -2, 3};
    std::vector<int> right{4, 5, 6};
    int distance = 0;
    // In this case, the return code should be 2 (since negative values are present).
    EXPECT_EQ(test.computeDistance(left, right, distance), 2);
}
/**
 * @brief Unit test for the HistorianHysteria::computeDistance method.
 *        This test verifies the case where the two inputs are identical.
 */
TEST(ComputeDistance, ZeroDistance) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, 2, 3};
    std::vector<int> right{1, 2, 3};
    int distance = 0;
    // In this case, the return code should be 0 (since no error has been detected).
    EXPECT_EQ(test.computeDistance(left, right, distance), 0);
    // Then, the actual measured distance should be 0, since the lists are equal.
    EXPECT_EQ(distance, 0);
}

//> Test cases for the computeSimilarity() function.
/**
 * @brief Unit test for the HistorianHysteria::computeSimilarity method.
 *        This test verifies the basic functionality of the computeSimilarity function.
 */
TEST(ComputeSimilarity, BasicCase) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, 2, 3, 2};
    std::vector<int> right{2, 3, 4, 2};
    int similarity = 0;
    std::unordered_map<int, std::pair<int, int>> similarity_map;
    // The input is valid, so there should be no returned error code.
    EXPECT_EQ(test.computeSimilarity(left, right, similarity, similarity_map), 0);
    // The similarity between the two vectors should be 1*0 + 2*2*2 + 3*1 + 0*4 = 11.
    EXPECT_EQ(similarity, 11);
}
/**
 * @brief Unit test for the HistorianHysteria::computeSimilarity method.
 *        This test verifies the case where the input vectors have different sizes.
 */
TEST(ComputeSimilarity, DifferentSizes) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, 2};
    std::vector<int> right{1, 2, 3};
    int similarity = 0;
    std::unordered_map<int, std::pair<int, int>> similarity_map;
    // The left and right vector size are different, so the returned error code should be 1.
    EXPECT_EQ(test.computeSimilarity(left, right, similarity, similarity_map), 1);
}
/**
 * @brief Unit test for the HistorianHysteria::computeSimilarity method.
 *        This test verifies the case where a negative value is present.
 */
TEST(ComputeSimilarity, NegativeValues) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, -2, 3};
    std::vector<int> right{1, 2, 3};
    int similarity = 0;
    std::unordered_map<int, std::pair<int, int>> similarity_map;
    // There are negative values, so the returned error code should be 2.
    EXPECT_EQ(test.computeSimilarity(left, right, similarity, similarity_map), 2);
}
/**
 * @brief Unit test for the HistorianHysteria::computeSimilarity method.
 *        This test verifies the case where the input vectors are completely different.
 */
TEST(ComputeSimilarity, ZeroSimilarity) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, 2, 3};
    std::vector<int> right{4, 5, 6};
    int similarity = 0;
    std::unordered_map<int, std::pair<int, int>> similarity_map;
    // The input is valid, so there should be no error code returned.
    EXPECT_EQ(test.computeSimilarity(left, right, similarity, similarity_map), 0);
    // No overlap between left and right, so similarity should be 0
    EXPECT_EQ(similarity, 0);
}
/**
 * @brief Unit test for the HistorianHysteria::computeSimilarity method.
 *        This test verifies the case where the input vectors are the same.
 */
TEST(ComputeSimilarity, AllOverlap) {
    // Instanciate the test class.
    HistorianHysteria test("");
    // Initialize the test input.
    std::vector<int> left{1, 2, 3};
    std::vector<int> right{1, 2, 3};
    int similarity = 0;
    std::unordered_map<int, std::pair<int, int>> similarity_map;
    // The input is valid, so there should be no error code returned.
    EXPECT_EQ(test.computeSimilarity(left, right, similarity, similarity_map), 0);
    // Each id appears once in both: 1*1*1 + 2*1*1 + 3*1*1 = 6.
    EXPECT_EQ(similarity, 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


