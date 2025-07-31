/**
 * @file red_reports.hpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the header of the Red-Nosed Reports problem proposed in Day 2 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

#ifndef _DAY_2_RED_REPORTS_HPP_
#define _DAY_2_RED_REPORTS_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> DEPENDENCIES
//> C/C++ libraries
#include <string>
#include <unordered_map>
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
class RedReports : public BaseAdventDay {
/**
 * @class RedReports
 * @brief A class to process the Advent of Code Day 2 problem.
 *
 * Inherits from BaseAdventDay. This class loads reports, evaluates their safety, and supports tolerance-based evaluation.
 */

 public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> CONSTRUCTORS
    /**
     * @brief Constructor of the class. Declared as explicit to prevent ambiguous instantiation.
     * @param _filename Name of the file containing the report data.
     */
    explicit RedReports(std::string _filename);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> DESTRUCTORS
    /**
     * @brief Destructor of the class.
     */
    ~RedReports();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /**
     * @brief Run the code to process the input list.
     * @return 0 on success, error code otherwise.
     */
    int run();
    /**
     * @brief Load data from a text file and fill the map with the reports.
     * @details Temporal complexity: O(n), Space complexity: O(n).
     * @param _fn Path to the input file.
     * @param _reports Output map of report ID to level data.
     * @return 0 on success, non-zero on failure.
     */
    int loadDataFromFile(const std::string& _fn, std::unordered_map<int, std::vector<int>>& _reports);
    /**
     * @brief Check if a report is safe — has a consistent trend and consecutive level variations within 1–3.
     * @details Temporal complexity: O(n), Space complexity: O(1).
     * @param _levels The list of levels for a single report.
     * @return 1 if safe, 0 otherwise.
     */
    int isReportSafe(std::vector<int>& _levels);
    /**
     * @brief Check if a report is safe with damping — allowing one unsafe level to be ignored.
     * @details Temporal complexity: O(n), Space complexity: O(1).
     * @param _levels The list of levels for a single report.
     * @return 1 if safe with damping, 0 otherwise.
     */
    int isReportSafeWithDamping(std::vector<int>& _levels);
    /**
     * @brief Count the number of safe and damped-safe reports using the provided input map.
     * @details
     *   - Temporal complexity: O(n·k)
     *   - Space complexity: O(k)
     *   - where `k` is the average length of the reports.
     * @param _reports The report map to process.
     * @param _s_count Output: number of fully safe reports.
     * @param _d_count Output: number of damped-safe reports.
     * @return 0 on success, non-zero on error.
     */
    int countSafeReports(
      std::unordered_map<int, std::vector<int>>& _reports, int& _s_count, int& _d_count);
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
     * @brief The report data, mapping report ID to level list.
     */
    std::unordered_map<int, std::vector<int>> reports_;
    /**
     * @brief The number of safe reports.
     */
    int safe_count_;
    /**
     * @brief The number of safe reports after damping.
     */
    int damped_count_;
    //> FIXED / They cannot change during runtime. Declared as const.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _DAY_2_RED_REPORTS_HPP_
