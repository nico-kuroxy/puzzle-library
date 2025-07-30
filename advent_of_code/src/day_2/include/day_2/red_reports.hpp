/**********************************************************************************************************************/
//   author: nicolas.erbetti.k@gmail.com
//   brief: This file defines the header of the Red-Nosed Reports problem proposed in the day 2 of the advent of code.
//   copyright: © 2025 Nicolas Erbetti.
/**********************************************************************************************************************/

#ifndef _DAY_2_RED_REPORTS_HPP_
#define _DAY_2_RED_REPORTS_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> DEPENDENCIES
//> C/C++ libraries
#include <cmath>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
//> Custom-made libraries
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> GLOBAL VARIABLES
//> ATOMIC VARIABLES
//> OTHERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> CLASS DECLARATION
class RedReports {
/* A class to process the problem of day 2. */

 public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> CONSTRUCTORS
    /* Constructor of the class. Declared as explicit to prevent ambiguous instanciation. */
    explicit RedReports(std::string _filename);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> DESTRUCTORS
    /* Destructor of the class. */
    ~RedReports();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /* Run the code to process the input list. */
    int run();
    /* Load data from a text file and fill the vectors with the left and right ids.
       Temporal complexity: O(n).
       Space complexity: O(n). */
    int loadDataFromFile(const std::string& _fn, std::unordered_map<int, std::vector<int>>& _reports);
    /* Check if a report is safe, ie has a consistent trend of levels and whose consecutive level variation are within 1-3.
      Temporal complexity: O(n).
      Space complexity: O(1). */
    int isReportSafe(std::vector<int>& _levels);
    /* Apply the damping logic to the given report. */
    int dampReport
       (std::vector<int>& _levels, size_t& _index, int& _trend, int& _last_trend,
          int& _damping_treshold, int& _nb_damped, bool& _is_safe);
    /* Check if a report is safe, ie has a consistent trend of levels and whose consecutive level variation are within 1-3.
      We have a tolerance of 1 unsafe level, but this threshold is flexible.
      Temporal complexity: O(n).
      Space complexity: O(1). */
    int isReportSafeWithDamping(std::vector<int>& _levels, int _damping_threshold);
    /* Count the number of safe reports by calling isReportSafe().
      Temporal complexity: O(n).
      Space complexity: O(1).  */
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
    // The name of the file containing the data to process.
    std::string filename_;
    // The report data, which is a map of integers (id of the report) to vectors of integers (levels of the report).
    std::unordered_map<int, std::vector<int>> reports_;
    // The number of safe reports.
    int safe_count_;
    // The number of safe reports after damping.
    int damped_count_;
    //> FIXED / They cannot change during runtime. Declared as const.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _DAY_2_RED_REPORTS_HPP_
