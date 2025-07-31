/**
 * @file historian_hysteria.hpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the header of the Historian Hysteria problem proposed in Day 1 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

#ifndef _DAY_1_HISTORIAN_HYSTERIA_HPP_
#define _DAY_1_HISTORIAN_HYSTERIA_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> DEPENDENCIES
//> C/C++ libraries
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
class HistorianHysteria : public BaseAdventDay {
/**
 * @class HistorianHysteria
 * @brief Processes the Advent of Code Day 1 problem, handling input data and computing required metrics.
 *
 * Inherits from BaseAdventDay. This class loads data from a file, processes left and right ID lists,
 * and computes distance and similarity metrics between them.
 *
 */

 public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> CONSTRUCTORS
    /**
     * @brief Constructs a HistorianHysteria object with the specified filename.
     *
     * This explicit constructor initializes the HistorianHysteria instance using the provided
     * filename, which is expected to reference the data source required by the class.
     *
     * @param _filename The name of the file to be used for initialization.
     */
    explicit HistorianHysteria(std::string _filename);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> DESTRUCTORS
    /**
     * @brief Destructor for the HistorianHysteria class.
     *
     * Cleans up any resources allocated by HistorianHysteria.
     */
    ~HistorianHysteria();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /**
     * @brief Run the code to process the input list.
     * @return 0 if success, non-zero error code otherwise.
     */
    int run();
    /**
     * @brief Load data from a text file and fill the vectors with the left and right ids.
     * @details Temporal complexity: O(n), Space complexity: O(n).
     * @param _fn The filename to load.
     * @param _data_l Output vector of left IDs.
     * @param _data_r Output vector of right IDs.
     * @return 0 if success, non-zero on error.
     */
    int loadDataFromFile(const std::string& _fn, std::vector<int>& _data_l, std::vector<int>& _data_r);
    /**
     * @brief Compute the distance between the left and right ids.
     * @details Temporal complexity: O(n log n), Space complexity: O(1).
     * @param _data_l Vector of left IDs.
     * @param _data_r Vector of right IDs.
     * @param _distance Output distance.
     * @return 0 if success, non-zero on error.
     */
    int computeDistance(std::vector<int>& _data_l, std::vector<int>& _data_r, int& _distance);
    /**
     * @brief Compute the similarity between the left and right ids.
     * @details Temporal complexity: O(n), Space complexity: O(n).
     * @param _data_l Vector of left IDs.
     * @param _data_r Vector of right IDs.
     * @param _similarity Output similarity score.
     * @param _similarity_map Output map of similarities.
     * @return 0 if success, non-zero on error.
     */
    int computeSimilarity(
      std::vector<int>& _data_l, std::vector<int>& _data_r,
         int& _similarity, std::unordered_map<int, std::pair<int, int>>& _similarity_map);
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
     * @brief The vector containing the left ids.
     */
    std::vector<int> data_l_;
    /**
     * @brief The vector containing the right ids.
     */
    std::vector<int> data_r_;
    /**
     * @brief The computed distance between the left and right ids.
     */
    int distance_;
    /**
     * @brief The computed similarity between the left and right ids.
     */
    int similarity_;
    /**
     * @brief The map containing the number of each id from the left list counted in the right list.
     */
    std::unordered_map<int, std::pair<int, int>> similarity_map_;
    //> FIXED / They cannot change during runtime. Declared as const.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _DAY_1_HISTORIAN_HYSTERIA_HPP_
