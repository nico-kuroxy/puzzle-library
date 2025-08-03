/**
 * @file test_red_reports.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the test cases of the Red Report problem proposed in Day 2 of the Advent of Code.
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
#include <day_2/red_reports.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> TEST CASES

//> Test cases for the loadDataFromFile() function.
/**
 * @brief Unit test for the RedReports::loadDataFromFile method.
 *        This test verifies that a correctly formatted file is loaded properly.
 */
TEST(LoadDataFromFile, ValidInput) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::unordered_map<int, std::vector<int>> reports;
    // Create a temporary file with valid data.
    const std::string filename = "test_input_valid_day2.txt";
    std::ofstream out(filename);
    out << "1 2 3\n4 5 6\n7 8 9\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, reports);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // Check that data was parsed correctly.
    EXPECT_EQ(reports[1], std::vector<int>({1, 2, 3}));
    EXPECT_EQ(reports[2], std::vector<int>({4, 5, 6}));
    EXPECT_EQ(reports[3], std::vector<int>({7, 8, 9}));
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the RedReports::loadDataFromFile method.
 *        This test verifies the case where the input file does not exist.
 */
TEST(LoadDataFromFile, FileNotFound) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::unordered_map<int, std::vector<int>> reports;
    // Attempt to load from a non-existent file.
    int result = test.loadDataFromFile("nonexistent_file.txt", reports);
    // The return code should be 1 (file could not be opened).
    EXPECT_EQ(result, 1);
}
/**
 * @brief Unit test for the RedReports::loadDataFromFile method.
 *        This test verifies the case where a line contains negative values.
 */
TEST(LoadDataFromFile, NegativeValues) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::unordered_map<int, std::vector<int>> reports;
    // Create a temporary file with negative input.
    const std::string filename = "test_input_negative_day2.txt";
    std::ofstream out(filename);
    out << "1 -2 3\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, reports);
    // The return code should be 2 (invalid negative values).
    EXPECT_EQ(result, 2);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}

//> Test cases for the isReportSafe() function.
/**
 * @brief Unit test for the RedReports::isReportSafe method.
 *        This test verifies the case where a report is clearly safe.
 */
TEST(IsReportSafe, SafeReport) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::vector<int> levels{1, 2, 3};
    // Should return true (safe report).
    EXPECT_TRUE(test.isReportSafe(levels));
}
/**
 * @brief Unit test for the RedReports::isReportSafe method.
 *        This test verifies the case where a report has a trend break.
 */
TEST(IsReportSafe, UnsafeTrendChange) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::vector<int> levels{1, 2, 1};
    // Should return false (unsafe due to trend change).
    EXPECT_FALSE(test.isReportSafe(levels));
}
/**
 * @brief Unit test for the RedReports::isReportSafe method.
 *        This test verifies the case where level differences exceed the allowed range.
 */
TEST(IsReportSafe, UnsafeDeltaTooLarge) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::vector<int> levels{1, 5, 6};
    // Should return false (delta > 3).
    EXPECT_FALSE(test.isReportSafe(levels));
}

//> Test cases for the isReportSafeWithDamping() function.
/**
 * @brief Unit test for the RedReports::isReportSafeWithDamping method.
 *        This test verifies the case where the report is made safe by removing one level.
 */
TEST(IsReportSafeWithDamping, DampingWorks) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::vector<int> levels{1, 5, 3};
    // Should return true (becomes safe after removing 5).
    EXPECT_TRUE(test.isReportSafeWithDamping(levels));
}
/**
 * @brief Unit test for the RedReports::isReportSafeWithDamping method.
 *        This test verifies the case where no removal makes the report safe.
 */
TEST(IsReportSafeWithDamping, DampingFails) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::vector<int> levels{10, 2, 10};
    // Should return false.
    EXPECT_FALSE(test.isReportSafeWithDamping(levels));
}

//> Test cases for the countSafeReports() function.
/**
 * @brief Unit test for the RedReports::countSafeReports method.
 *        This test verifies the correct count of safe and damped reports.
 */
TEST(CountSafeReports, MixedReports) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::unordered_map<int, std::vector<int>> reports = {
        {1, {1, 2, 3}},           // Safe
        {2, {10, 2, 10}},         // Unsafe
        {3, {1, 5, 3}},           // Damped safe
    };
    int safe = 0, damped = 0;
    // Execute the function.
    int result = test.countSafeReports(reports, safe, damped);
    // Should succeed.
    EXPECT_EQ(result, 0);
    // Only one fully safe report.
    EXPECT_EQ(safe, 1);
    // Two reports are safe with damping (1 is already safe, 1 needs damping).
    EXPECT_EQ(damped, 2);
}
/**
 * @brief Unit test for the RedReports::countSafeReports method.
 *        This test verifies the error case with an empty report.
 */
TEST(CountSafeReports, EmptyReport) {
    // Instantiate the test class.
    RedReports test("");
    // Initialize the test input.
    std::unordered_map<int, std::vector<int>> reports = {
        {1, {}}
    };
    int safe = 0, damped = 0;
    // Should return error code 1.
    EXPECT_EQ(test.countSafeReports(reports, safe, damped), 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


