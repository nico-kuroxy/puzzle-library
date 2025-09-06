/**
 * @file test_person_handler.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the test cases of the Person Handler problem.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <gtest/gtest.h>
#include <iostream>
//> Custom-made libraries
#include <person_handling/person_handler.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> TEST CASES

//> TEST CASES FOR THE findFirstPerson() METHOD.
/**
 * @brief Unit test for the PersonHandler::findFirstPerson method.
 *        This test verifies that an empty list returns the proper error code.
 */
TEST(FindFirstPerson, EmptyList) {
    // Initialize the test variables.
    std::string name;
    std::vector<Person> list;
    // Call the tested function.
    int result = PersonHandler::findFirstPerson(list, name);
    // The return code should be -1 (failure).
    EXPECT_EQ(result, -1);
}
/**
 * @brief Unit test for the PersonHandler::findFirstPerson method.
 *        This test verifies that a list with a single name returns the proper result.
 */
TEST(FindFirstPerson, OnePerson) {
    // Initialize the test variables.
    std::string name;
    std::vector<Person> list = {Person("Kholin", 22)};
    // Call the tested function.
    int result = PersonHandler::findFirstPerson(list, name);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The name of the first person should be "Kholin".
    EXPECT_EQ(name, "Kholin");
}
/**
 * @brief Unit test for the PersonHandler::findFirstPerson method.
 *        This test verifies that a list with multiple names returns the proper result.
 */
TEST(FindFirstPerson, MultiplePerson) {
    // Initialize the test variables.
    std::string name;
    std::vector<Person> list = {Person("Kholin", 22), Person("Dazar", 17), Person("Davar", 17), Person("Sadeas", 50)};
    // Call the tested function.
    int result = PersonHandler::findFirstPerson(list, name);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The name of the first person should be "Davar".
    EXPECT_EQ(name, "Davar");
}
/**
 * @brief Unit test for the PersonHandler::findFirstPerson method.
 *        This test verifies that a list with only the same names returns the proper result.
 */
TEST(FindFirstPerson, SameNames) {
    // Initialize the test variables.
    std::string name;
    std::vector<Person> list = {Person("Kholin", 22), Person("Kholin", 22), Person("Kholin", 22), Person("Kholin", 22)};
    // Call the tested function.
    int result = PersonHandler::findFirstPerson(list, name);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The name of the first person should be "Kholin".
    EXPECT_EQ(name, "Kholin");
}

//> TEST CASES FOR THE findMeanDevAge() METHOD.
/**
 * @brief Unit test for the PersonHandler::findMeanDevAge method.
 *        This test verifies that an empty list returns the proper error code.
 */
TEST(FindMeanDevAge, EmptyList) {
    // Initialize the test variables.
    float mean, dev;
    std::vector<Person> list;
    // Call the tested function.
    int result = PersonHandler::findMeanDevAge(list, mean, dev);
    // The return code should be -1 (failure).
    EXPECT_EQ(result, -1);
}
/**
 * @brief Unit test for the PersonHandler::findMeanDevAge method.
 *        This test verifies that a list with a single person returns the proper result.
 */
TEST(FindMeanDevAge, OnePerson) {
    // Initialize the test variables.
    float mean, dev;
    std::vector<Person> list = {Person("Kholin", 22)};
    // Call the tested function.
    int result = PersonHandler::findMeanDevAge(list, mean, dev);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The mean and standard dev should be 22 and 0.
    EXPECT_EQ(mean, 22);
    EXPECT_EQ(dev, 0);
}
/**
 * @brief Unit test for the PersonHandler::findMeanDevAge method.
 *        This test verifies that a list with multiple person returns the proper result.
 */
TEST(FindMeanDevAge, MultiplePerson) {
    // Initialize the test variables.
    float mean, dev;
    std::vector<Person> list = {Person("Kholin", 22), Person("Dazar", 17), Person("Davar", 17), Person("Sadeas", 50)};
    // Call the tested function.
    int result = PersonHandler::findMeanDevAge(list, mean, dev);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The mean and standard dev should be 22 and 0.
    EXPECT_EQ(mean, 26.5);
    EXPECT_NEAR(dev, 13.7204, 10e-4);
}
/**
 * @brief Unit test for the PersonHandler::findMeanDevAge method.
 *        This test verifies that a list with only the same persons returns the proper result.
 */
TEST(FindMeanDevAge, SameNames) {
    // Initialize the test variables.
    float mean, dev;
    std::vector<Person> list = {Person("Kholin", 22), Person("Kholin", 22), Person("Kholin", 22), Person("Kholin", 22)};
    // Call the tested function.
    int result = PersonHandler::findMeanDevAge(list, mean, dev);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The mean and standard dev should be 22 and 0.
    EXPECT_EQ(mean, 22);
    EXPECT_EQ(dev, 0);
}

//> TEST CASES FOR THE findMedian() METHOD.
/**
 * @brief Unit test for the PersonHandler::findMedian method.
 *        This test verifies that an empty list returns the proper error code.
 */
TEST(FindMedian, EmptyList) {
    // Initialize the test variables.
    int median;
    std::string name;
    std::vector<Person> list;
    // Call the tested function.
    int result = PersonHandler::findMedian(list, median, name);
    // The return code should be -1 (failure).
    EXPECT_EQ(result, -1);
}
/**
 * @brief Unit test for the PersonHandler::findMedian method.
 *        This test verifies that a list with a single person returns the proper result.
 */
TEST(FindMedian, OnePerson) {
    // Initialize the test variables.
    int median;
    std::string name;
    std::vector<Person> list = {Person("Kholin", 22)};
    // Call the tested function.
    int result = PersonHandler::findMedian(list, median, name);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The median should be 22 and the name should be Kholin.
    EXPECT_EQ(median, 22);
    EXPECT_EQ(name, "Kholin");
}
/**
 * @brief Unit test for the PersonHandler::findMedian method.
 *        This test verifies that a list with multiple person returns the proper result.
 */
TEST(FindMedian, MultiplePerson) {
    // Initialize the test variables.
    int median;
    std::string name;
    std::vector<Person> list = {Person("Kholin", 22), Person("Dazar", 17), Person("Davar", 17), Person("Sadeas", 50), Person("Verino", 42)};
    // Call the tested function.
    int result = PersonHandler::findMedian(list, median, name);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The median should be 22 and the name should be Kholin.
    EXPECT_EQ(median, 22);
    EXPECT_EQ(name, "Kholin");
}
/**
 * @brief Unit test for the PersonHandler::findMedian method.
 *        This test verifies that a list with only the same persons returns the proper result.
 */
TEST(FindMedian, SameNames) {
    // Initialize the test variables.
    int median;
    std::string name;
    std::vector<Person> list = {Person("Kholin", 22), Person("Kholin", 22), Person("Kholin", 22), Person("Kholin", 22), Person("Kholin", 22)};
    // Call the tested function.
    int result = PersonHandler::findMedian(list, median, name);
    // The return code should be 0 (success).
    EXPECT_EQ(result, 0);
    // The median should be 22 and the name should be Kholin.
    EXPECT_EQ(median, 22);
    EXPECT_EQ(name, "Kholin");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


