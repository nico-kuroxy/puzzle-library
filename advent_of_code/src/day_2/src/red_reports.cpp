/**********************************************************************************************************************/
//   author: nicolas.erbetti.k@gmail.com
//   brief: This file defines the source of the Red-Nosed Reports problem proposed in the day 2 of the advent of code.
//   copyright: © 2025 Nicolas Erbetti.
/**********************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
//> Custom-made libraries
#include <day_2/red_reports.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> CONSTRUCTORS
RedReports::RedReports(std::string _filename) {
    //> INITIALIZING EVERY ATTRIBUTE.
    this->filename_ = _filename;
    this->reports_ = std::unordered_map<int, std::vector<int>>();
    this->safe_count_ = 0;
    this->damped_count_ = 0;
    //> LOGGING.
    std::cout << "RedReports initialized with file: " << this->filename_ << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DESTRUCTORS
RedReports::~RedReports() {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> FUNCTIONS
int RedReports::run() {
    // Load data from file.
    if (this->loadDataFromFile(this->filename_, this->reports_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error loading data from file: " << this->filename_ << std::endl;
        // And return an error code.
        return 1;
    }
    // Count the number of safe reports.
    if (this->countSafeReports(this->reports_, this->safe_count_, this->damped_count_)) {
        // If there was an error counting the safe reports, log it.
        std::cerr << "Error counting safe reports." << std::endl;
        // And return an error code.
        return 2;
    }
    // Return success.
    return 0;
}
int RedReports::loadDataFromFile(const std::string& _fn, std::unordered_map<int, std::vector<int>>& _reports) {
    // Initialize the function variables.
    int id = 0;
    int level;
    std::string line;
    // Reset the report map.
    _reports.clear();
    // Try to open the file.
    std::ifstream file(_fn);
    // If the file could not be opened, return an error.
    if (!file) {
        // Log the error.
        std::cerr << "Failed to open file." << std::endl;
        // Return.
        return 1;
    }
    // Read the file line by line and parse the data.
    while (std::getline(file, line)) {
        // Update the line id.
        id += 1;
        // Assuming each line contains intergers, separated by spaces.
        std::istringstream iss(line);
        // Try to read the two ids from the line.
        while (iss >> level) {
            // Check if both ids are positive integers.
            if (level < 0) {
                // If not, print an error message.
                std::cerr << "Error: [" << level << "] must be a positive integer." << std::endl;
                // And return an error code.
                return 2;
            }
            // Add the level to the proper report.
            _reports[id].push_back(level);
        }
    }
    // Close the file.
    file.close();
    // Return.
    return 0;
}
int RedReports::isReportSafe(std::vector<int>& _levels) {
    // Initialize flag for the report.
    bool is_safe = true;
    int trend = 0;  // 0 means no trend, 1 means increasing, -1 means decreasing.
    // Iterate through the levels of the report.
    for (size_t i = 1; i < _levels.size(); i++) {
        // Initialize the trend by assigning it the sign of the first difference.
        if (abs(abs(_levels[i] - _levels[i - 1]) - 2) > 1) {
            // We check if the successive levels are within safe range (between 1 and 3 or between -1 and -3).
            // We can center this condition by shifting the absolute difference of the levels by 2.
            // Then update the flag.
            is_safe = false;
            // Then break the loop.
            break;
        } else if (!trend) {
            trend = std::copysign(1, _levels[i] - _levels[i - 1]);
        } else if (trend != std::copysign(1, _levels[i] - _levels[i - 1])) {
            // Otherwise, we check if the trend has changed and log.
            // Then update the flag.
            is_safe = false;
            // Then break the loop if the trend.
            break;
        }
    }
    // Return the safety status of the report.
    return is_safe;
}
int RedReports::isReportSafeWithDamping(std::vector<int>& _levels) {
    // Initialize flag for the report.
    bool is_safe = false;
    // Check if the report is safe with the damping.
    for (int i = 0; i < _levels.size(); i++) {
        // Create a temporary vector to hold the levels.
        std::vector<int> temp_levels = _levels;
        // We remove the current level.
        temp_levels.erase(temp_levels.begin() + i);
        // We check if the report is now safe.
        if (this->isReportSafe(temp_levels)) {
            // If it is, we update the flag.
            is_safe = true;
            // And we can exit the loop early.
            break;
        }
    }
    // Return the safety status of the report.
    return is_safe;
}
int RedReports::countSafeReports(std::unordered_map<int, std::vector<int>>& _reports, int& _s_count, int& _d_count) {
    // Initialize function variables.
    _s_count = 0;
    _d_count = 0;
    // Iterate through the reports.
    for (auto& report : _reports) {
        // Check if the report has at least one level.
        if (report.second.empty()) {
            // Log the error.
            std::cerr << "Error: Report with ID [" << report.first << "] has no levels." << std::endl;
            // Return the error code.
            return 1;
        }
        // Check if the report is safe.
        if (this->isReportSafe(report.second)) {
            // We increment the safe count.
            _s_count += 1;
        } else {
            // Log the unsafe report.
            std::cerr << "Unsafe report with ID [" << report.first << "] detected." << std::endl;
        }
        // Check if the report is safe with the damping factor.
        if (this->isReportSafeWithDamping(report.second)) {
            // We increment the safe count.
            _d_count += 1;
        } else {
            // Log the unsafe report.
            std::cerr << "Unsafe damped report with ID [" << report.first << "] detected." << std::endl;
        }
    }
    // Log the final safe count.
    std::cout << "Total number of safe reports: " << _s_count << std::endl;
    std::cout << "Total number of safe damped reports: " << _d_count << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> ACCESSERS
//> GETTERS
//> SETTERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
