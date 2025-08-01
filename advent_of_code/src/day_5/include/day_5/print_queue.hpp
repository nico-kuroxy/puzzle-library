/**
 * @file print_queue.hpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the header of the Print Queue problem proposed in Day 5 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

#ifndef _DAY_5_PRINT_QUEUE_HPP_
#define _DAY_5_PRINT_QUEUE_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> DEPENDENCIES
//> C/C++ libraries
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
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
class PrintQueue : public BaseAdventDay {
/**
 * @class PrintQueue
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
    explicit PrintQueue(std::string _filename);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> DESTRUCTORS
    /**
     * @brief Destructor of the class.
     */
    ~PrintQueue();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /**
     * @brief Declare a run function to comply with the base class.
     * @return int Returns 0 on success, or a non-zero error code on failure.
     */
    int run();
   /**
    * @brief Loads data from a file and populates page rules and updates.
    *        The time complexity is O(r + p), and the space complexity is O(r + p).
    *        With r the number of rules, p is the total number of pages to eventually update.
    * @param _fn The filename from which to load the data.
    * @param _page_rules Reference to a vector that will be filled with pairs representing page rules.
    * @param _updates Reference to a vector of pair of unordered maps + int that will be filled with the page information.
    * @return int Returns 0 on success, or a non-zero error code on failure.
    */
    int loadDataFromFile(
      const std::string& _fn, std::vector<std::pair<int, int>>& _page_rules,
         std::vector<std::pair<std::unordered_map<int, int>, int>>& _updates);
   /**
    * @brief Checks if the given update is valid according to the specified rules. 
    *        The time complexity is O(1), and the space complexity is O(1).
    * @param _update An unordered map representing the update to be validated. Keys and values are integers.
    * @param _rule A pair of integers, representing a validation rule.
    * @return bool Returns true if the update is valid, false otherwise.
    */
    bool isUpdateValid(const std::unordered_map<int, int>& _update, const std::pair<int, int>& _rule);
   /**
    * @brief Applies a rule to update a queue and adjusts the middle page accordingly.
    *        The time complexity is O(1), and the space complexity is O(1).
    * @param _update Reference to an unordered_map representing the current update state.
    * @param _rule A pair of integers representing the rule to be applied.
    * @param _middle_page Reference to an integer representing the current middle page, which may be modified.
    * @return int Returns 0 on success, or a non-zero error code on failure.
    */
    int fixUpdate(std::unordered_map<int, int>& _update, const std::pair<int, int>& _rule, int& _middle_page);
   /**
    * @brief Checks and applies updates based on a set of rules.
    *        The time complexity is O(r*u), or O(r!*u) in the worst case with the fixing of invalid updates, and the space complexity is O(1).
    *        This is potentially very bad, but only occurs is the updates are always breaking all previous rules when fixing one.
    *        With r the number of rules, u the number of updates. This could be improved with either a proper rule checking (to make sure that no rules are repeated multiple times, for instance),
    *        or by graphing the rules together. If the rules are valid, then we will create subsets of pages order that we can use to make everything faster.
    * @param _updates A vector of unordered maps and int, where each map represents updates and are associated with their middle page.
    * @param _rules A vector of pairs, where each pair represents a rule with two integers.
    * @param _result An int with the sum of the middle page number from the correctly-ordered updates.
    * @param _result_fixed An int with the sum of the middle page number from the previously invalid updates.
    * @return int Returns 0 on success, or a non-zero error code on failure.
    */
    int checkUpdates(
      std::vector<std::pair<std::unordered_map<int, int>, int>>& _updates,
         std::vector<std::pair<int, int>> _rules, int& _result, int& _result_fixed);
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
     * @brief The list of page rules that the newly produced pages must follow.
     *        The first int is the number of the page that needs to appear before the page represented by the second int.
     */
    std::vector<std::pair<int, int>> page_rules_;
    /**
     * @brief The list of updates that we want to produce. 
     *        Each element contains an unordered map of the pages, and the id of the middle page.
     *        The key is the page number and the value is its index in the original list.
     */
    std::vector<std::pair<std::unordered_map<int, int>, int>> updates_;
    /**
     * @brief The sum of the middle page number from the correctly-ordered updates.
     */
    int result_;
    /**
     * @brief The sum of the middle page number from the uncorrectly-ordered updates after fixing them.
     */
    int result_fixed_;
    //> FIXED / They cannot change during runtime. Declared as const.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _DAY_5_PRINT_QUEUE_HPP_

