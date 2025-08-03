/**
 * @file test_print_queue.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the test cases of the Print Queue problem proposed in Day 5 of the Advent of Code.
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
#include <day_5/print_queue.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> TEST CASES

//> Test cases for the loadDataFromFile() function.
/**
 * @brief Unit test for the PrintQueue::loadDataFromFile method.
 *        This test verifies that a correctly formatted input file is loaded properly.
 */
TEST(LoadDataFromFile, ValidInput) {
    // Instantiate the test class.
    PrintQueue test("");
    // Initialize containers for page rules and updates.
    std::vector<std::pair<int,int>> page_rules;
    std::vector<std::pair<std::unordered_map<int,int>, int>> updates;
    // Create a temporary file with valid data: rules and updates separated by a blank line.
    const std::string filename = "test_input_valid.txt";
    std::ofstream out(filename);
    out << "1|2\n3|4\n\n10,20,30\n40,50,60\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, page_rules, updates);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The page_rules vector should contain two entries.
    ASSERT_EQ(page_rules.size(), 2);
    EXPECT_EQ(page_rules[0], std::make_pair(1, 2));
    EXPECT_EQ(page_rules[1], std::make_pair(3, 4));
    // The updates vector should contain two updates.
    ASSERT_EQ(updates.size(), 2);
    // Check first update pages and middle page.
    EXPECT_EQ(updates[0].second, 20);
    EXPECT_TRUE(updates[0].first.find(10) != updates[0].first.end());
    EXPECT_TRUE(updates[0].first.find(20) != updates[0].first.end());
    EXPECT_TRUE(updates[0].first.find(30) != updates[0].first.end());
    // Check second update pages and middle page.
    EXPECT_EQ(updates[1].second, 50);
    EXPECT_TRUE(updates[1].first.find(40) != updates[1].first.end());
    EXPECT_TRUE(updates[1].first.find(50) != updates[1].first.end());
    EXPECT_TRUE(updates[1].first.find(60) != updates[1].first.end());
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the PrintQueue::loadDataFromFile method.
 *        This test verifies behavior when the input file does not exist.
 */
TEST(LoadDataFromFile, FileNotFound) {
    // Instantiate the test class.
    PrintQueue test("");
    // Initialize containers for page rules and updates.
    std::vector<std::pair<int,int>> page_rules;
    std::vector<std::pair<std::unordered_map<int,int>, int>> updates;
    // Attempt to load data from a non-existent file.
    int result = test.loadDataFromFile("nonexistent_file.txt", page_rules, updates);
    // The return code should be 1 (file could not be opened).
    EXPECT_EQ(result, 1);
}
/**
 * @brief Unit test for the PrintQueue::loadDataFromFile method.
 *        This test verifies behavior when a rule line is missing the '|' separator.
 */
TEST(LoadDataFromFile, InvalidRuleFormat) {
    // Instantiate the test class.
    PrintQueue test("");
    // Initialize containers for page rules and updates.
    std::vector<std::pair<int,int>> page_rules;
    std::vector<std::pair<std::unordered_map<int,int>, int>> updates;
    // Create a temporary file with invalid rule (missing '|').
    const std::string filename = "test_input_invalid_rule.txt";
    std::ofstream out(filename);
    out << "1-2\n\n10,20,30\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, page_rules, updates);
    // The return code should be 2 (invalid rule format).
    EXPECT_EQ(result, 2);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the PrintQueue::loadDataFromFile method.
 *        This test verifies behavior when rule IDs are negative.
 */
TEST(LoadDataFromFile, NegativeRuleIDs) {
    // Instantiate the test class.
    PrintQueue test("");
    // Initialize containers for page rules and updates.
    std::vector<std::pair<int,int>> page_rules;
    std::vector<std::pair<std::unordered_map<int,int>, int>> updates;
    // Create a temporary file with negative page IDs in the rule.
    const std::string filename = "test_input_negative_rule.txt";
    std::ofstream out(filename);
    out << "-1|2\n\n10,20,30\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, page_rules, updates);
    // The return code should be 3 (negative page IDs).
    EXPECT_EQ(result, 3);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}
/**
 * @brief Unit test for the PrintQueue::loadDataFromFile method.
 *        This test verifies behavior when update pages contain invalid integers.
 */
TEST(LoadDataFromFile, InvalidUpdatePages) {
    // Instantiate the test class.
    PrintQueue test("");
    // Initialize containers for page rules and updates.
    std::vector<std::pair<int,int>> page_rules;
    std::vector<std::pair<std::unordered_map<int,int>, int>> updates;
    // Create a temporary file with invalid update pages (non-integer string).
    const std::string filename = "test_input_invalid_update.txt";
    std::ofstream out(filename);
    out << "1|2\n\n10,abc,30\n";
    out.close();
    // Attempt to load data from the file.
    int result = test.loadDataFromFile(filename, page_rules, updates);
    // The return code should be 5 (invalid page integer in updates).
    EXPECT_EQ(result, 5);
    // Clean up the temporary file.
    std::filesystem::remove(filename);
}

//> Test cases for the isUpdateValid() function.
/**
 * @brief Unit test for the PrintQueue::isUpdateValid method.
 *        This test verifies that an update is valid when the order respects the rule.
 */
TEST(IsUpdateValid, ValidOrder) {
    // Instantiate the test class.
    PrintQueue test("");
    // Prepare an update where page 1 appears before page 2.
    std::unordered_map<int, int> update = {{1, 0}, {2, 1}, {3, 2}};
    std::pair<int, int> rule = {1, 2};
    // The update is valid because page 1 index < page 2 index.
    EXPECT_TRUE(test.isUpdateValid(update, rule));
}
/**
 * @brief Unit test for the PrintQueue::isUpdateValid method.
 *        This test verifies that an update is invalid when the order violates the rule.
 */
TEST(IsUpdateValid, InvalidOrder) {
    // Instantiate the test class.
    PrintQueue test("");
    // Prepare an update where page 1 appears after page 2.
    std::unordered_map<int, int> update = {{1, 2}, {2, 0}, {3, 1}};
    std::pair<int, int> rule = {1, 2};
    // The update is invalid because page 1 index > page 2 index.
    EXPECT_FALSE(test.isUpdateValid(update, rule));
}

//> Test cases for the fixUpdate() function.
/**
 * @brief Unit test for the PrintQueue::fixUpdate method.
 *        This test verifies that fixUpdate swaps positions of pages and updates middle page if needed.
 */
TEST(FixUpdate, SwapPositionsAndMiddlePage) {
    // Instantiate the test class.
    PrintQueue test("");
    // Prepare an update where page 1 and page 2 violate the order.
    std::unordered_map<int, int> update = {{1, 2}, {2, 0}, {3, 1}};
    std::pair<int, int> rule = {1, 2};
    int middle_page = 1;
    // Fix the update.
    int result = test.fixUpdate(update, rule, middle_page);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // Positions of page 1 and 2 should be swapped.
    EXPECT_EQ(update[1], 0);
    EXPECT_EQ(update[2], 2);
    // Middle page should be updated from 1 to 2 (swapped).
    EXPECT_EQ(middle_page, 2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


