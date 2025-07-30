/**********************************************************************************************************************/
//   author: nicolas.erbetti.k@gmail.com
//   brief: This file defines the source of the Red-Nosed Reports problem proposed in the day 2 of the advent of code.
//   copyright: © 2025 Nicolas Erbetti.
/**********************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
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
            // std::cerr << "Warning: Report has unsafe variations." << std::endl;
            // Then update the flag.
            is_safe = false;
            // Then break the loop.
            break;
        } else if (!trend) {
            trend = std::copysign(1, _levels[i] - _levels[i - 1]);
        } else if (trend != std::copysign(1, _levels[i] - _levels[i - 1])) {
            // Otherwise, we check if the trend has changed and log.
            // std::cerr << "Warning: Report has inconsistent trend." << std::endl;
            // Then update the flag.
            is_safe = false;
            // Then break the loop if the trend.
            break;
        }
    }
    // Return the safety status of the report.
    return is_safe;
}
int RedReports::dampReport
    (std::vector<int>& _levels, size_t& _index, int& _trend, int& _last_trend,
        int& _damping_treshold, int& _nb_damped, bool& _is_safe) {
    // Check if the index is valid.
    if (_index <= 0 || _index >= _levels.size()) {
        // If not, print an error message.
        std::cerr << "Error: Invalid index " << _index << " for damping report." << std::endl;
        // And return an error code.
        return 1;
    }
    // Check the damping threshold.
    if (_nb_damped < _damping_treshold) {
        // If we have not damped yet, we can damp the report.
        _nb_damped += 1;
        // We check if the current index is the third one,
        // ie if it is the first level after a trend has been established.
        if (_index > 2) {
            // We update the current level to the previous one.
            // To keep the same number of levels while acting like the current level never existed.
            _levels[_index] = _levels[_index - 1];
            // We also revert the trend to the last one.
            _trend = _last_trend;
        } else {
            // We reset the trend to 0, as it does not matter what was the first trend.
            _trend = 0;
        }
        // And then we continue the loop.
        return 0;
    } else {
        // If we have already damped, we consider the report unsafe.
        _is_safe = false;
        // Then break the loop.
        return 1;
    }
    // Return.
    return 0;
}

int RedReports::isReportSafeWithDamping(std::vector<int>& _levels, int _damping_threshold) {
    // Initialize flag for the report.
    bool is_safe = true;
    int nb_damped = 0;
    int trend = 0;  // 0 means no trend, 1 means increasing, -1 means decreasing.
    int last_trend = 0;
    int last_value;
    // Iterate through the levels of the report.
    for (size_t i = 1; i < _levels.size(); i++) {
        // We check if the successive levels are within safe range (between 1 and 3 or between -1 and -3).
        // We can center this condition by shifting the absolute difference of the levels by 2.
        if (abs(abs(_levels[i] - _levels[i - 1]) - 2) > 1) {
            // Log the warning.
            // std::cerr << "Warning: Report has unsafe variations." << std::endl;
            // Then update the flag.
            if (this->dampReport(_levels, i, trend, last_trend, _damping_threshold, nb_damped, is_safe)) {
                break;
            } else {
                continue;
            }
        } else if (!trend) {
            // Initialize the trend by assigning it the sign of the first difference.
            trend = std::copysign(1, _levels[i] - _levels[i - 1]);
            // Check if the trend has changed.
            if (!trend) {
                if (this->dampReport(_levels, i, trend, last_trend, _damping_threshold, nb_damped, is_safe)) {
                    break;
                } else {
                    continue;
                }
            }
        } else if (trend != std::copysign(1, _levels[i] - _levels[i - 1])) {
            // Otherwise, we check if the trend has changed and log.
            // std::cerr << "Warning: Report has inconsistent trend." << std::endl;
            // Then update the flag.
            if (this->dampReport(_levels, i, trend, last_trend, _damping_threshold, nb_damped, is_safe)) {
                break;
            } else {
                continue;
            }
        }
        // If the trend has changed, we update the last trend.
        if (trend != last_trend) last_trend = trend;
        // Update the last value.
        last_value = _levels[i - 1];
    }
    if (!is_safe) {
        // Print the report levels.
        std::cerr << "Unsafe report levels: ";
        for (const auto& level : _levels) {
            std::cerr << level << " ";  // Print each level.
        }
        std::cerr << std::endl;  // New line after printing all levels.
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
            // std::cerr << "Error: Report with ID [" << report.first << "] has no levels." << std::endl;
            // Return the error code.
            return 1;
        }
        // Check if the report is safe.
        if (this->isReportSafe(report.second)) {
            // We increment the safe count.
            _s_count += 1;
        } else {
            // Log the unsafe report.
            // std::cerr << "Unsafe report with ID [" << report.first << "] detected." << std::endl;
        }
        // Check if the report is safe with the damping factor of 1
        if (this->isReportSafeWithDamping(report.second, 1)) {
            // We increment the safe count.
            _d_count += 1;
        } else {
            // Log the unsafe report.
            // std::cerr << "Unsafe damped report with ID [" << report.first << "] detected." << std::endl;
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
