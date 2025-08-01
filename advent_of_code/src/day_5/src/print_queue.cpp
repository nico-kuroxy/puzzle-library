/**
 * @file print_queue.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the source of the Print Queue problem proposed in Day 5 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
//> Custom-made libraries
#include <day_5/print_queue.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> CONSTRUCTORS
PrintQueue::PrintQueue(std::string _filename) :
    BaseAdventDay(_filename) {
    //> INITIALIZING EVERY ATTRIBUTE.
    this->page_rules_ = {};
    this->updates_ = {};
    this->result_ = 0;
    this->result_fixed_ = 0;
    //> LOGGING.
    std::cout << "PrintQueue initialized with file: " << this->filename_ << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DESTRUCTORS
PrintQueue::~PrintQueue() {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> FUNCTIONS
int PrintQueue::run() {
    // Load data from file.
    if (this->loadDataFromFile(this->filename_, this->page_rules_, this->updates_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error loading data from file: " << this->filename_ << std::endl;
        // And return an error code.
        return 1;
    }
    // Check the validity of the updates.
    if (this->checkUpdates(this->updates_, this->page_rules_, this->result_, this->result_fixed_)) {
        // If there was an error checking the updates, log it.
        std::cerr << "Error checking the updates." << std::endl;
        // And return an error code.
        return 2;
    }
    // Return success.
    return 0;
}
int PrintQueue::loadDataFromFile(
    const std::string& _fn, std::vector<std::pair<int, int>>& _page_rules,
        std::vector<std::pair<std::unordered_map<int, int>, int>>& _updates) {
    // Initialize the function variables.
    std::string line, first_page_str, second_page_str, extra_page_str;
    int first_page, second_page, extra_page;
    int page_index;
    bool are_rules_registered = false;
    std::pair<std::unordered_map<int, int>, int> update;
    std::vector<int> temp_update;
    // Reset the page variables.
    _page_rules.clear();
    _updates.clear();
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
        // Assuming each line contains the ids of the pages, separated by alphabetical characters.
        std::istringstream iss(line);
        // If we find an empty line, we consider that all rules has been registered.
        if (line == "") {
            // We update the flag.
            are_rules_registered = true;
            // And we go to the next line.
            continue;
        }
        // If we are not done registering the rules, we try to parse the current line.
        if (!are_rules_registered) {
            // Try to find the '|' separator.
            size_t separator = line.find('|');
            if (separator == std::string::npos) {
                // If not found, print an error message.
                std::cerr << "Invalid rule: " << line << ". Expected format: <id1>|<id2>" << std::endl;
                // And return an error code.
                return 2;
            }
            // Extract the left and right parts.
            std::string first_page_str = line.substr(0, separator);
            std::string second_page_str = line.substr(separator + 1);
            try {
                // Convert both parts to integers.
                first_page = std::stoi(first_page_str);
                second_page = std::stoi(second_page_str);
                // Check if both ids are positive integers.
                if (first_page < 0 || second_page < 0) {
                    // If not, print an error message.
                    std::cerr << "Error: ["
                        << first_page << ", " << second_page << "] must be positive int." << std::endl;
                    // And return an error code.
                    return 3;
                }
                // Add the ids to rules.
                _page_rules.push_back({first_page, second_page});
            } catch (const std::exception& e) {
                // If conversion fails, print an error message.
                std::cerr << "Invalid rule: " << line << ". Could not parse integers." << std::endl;
                // And return an error code.
                return 4;
            }
        } else {
            // Create a new update.
            temp_update.clear();
            update.first.clear();
            update.second = 0;
            page_index = 0;
            // Otherwise, we add the pages for a single update.
            while (std::getline(iss, extra_page_str, ',')) {
                // Process the string before the next separator.
                try {
                    // Try to find an integer before the next separator.
                    extra_page = std::stoi(extra_page_str);
                } catch (const std::exception& e) {
                    // If conversion fails, print an error message.
                    std::cerr << "Invalid page: " << extra_page << ". Could not parse integer." << std::endl;
                    // And return an error code
                    return 5;
                }
                // We check if the page is valid.
                if (extra_page < 0) {
                    // If the page is not positive, print an error message.
                    std::cerr << "Invalid page: " << extra_page << ". It must be positive." << std::endl;
                    // And return an error code
                    return 6;
                }
                // Add the page.
                temp_update.push_back(extra_page);
                update.first.insert({extra_page, page_index});
                // Increase the index.
                page_index += 1;
            }
            // We retrieve the value of the middle page.
            update.second = temp_update[((temp_update.size() - 1) / 2)];
            // And then we add the update to the list of updates.
            _updates.push_back(update);
        }
    }
    // Display the loaded rules.
    std::cout << "Loaded rules from file: " << _fn << std::endl;
    for (const auto& rule : _page_rules) {
        std::cout << rule.first << " | " << rule.second << std::endl;
    }
    // Display the loaded pages.
    std::cout << "Loaded updates from file: " << _fn << std::endl;
    for (const auto& update : _updates) {
        for (const auto& page : update.first) {
            std::cout << page.first << "(" << page.second << "), ";
        }
        std::cout << "Middle page is: " << update.second << std::endl;
        std::cout << std::endl;
    }
    // Close the file.
    file.close();
    // Return.
    return 0;
}
bool PrintQueue::isUpdateValid(
    const std::unordered_map<int, int>& _update, const std::pair<int, int>& _rule) {
    // Check if both pages of the rule are in the update.
    if ((_update.find(_rule.first) != _update.end()) && (_update.find(_rule.second) != _update.end())) {
        // Check if the index of the first page is LOWER than the index of the second.
        if (_update.at(_rule.first) > _update.at(_rule.second)) {
            // Return immediately.
            return false;
        }
    }
    // Return.
    return true;
}
int PrintQueue::fixUpdate(std::unordered_map<int, int>& _update, const std::pair<int, int>& _rule, int& _middle_page) {
    int temp;
    // Check if the pages exists in the map.
    if ((_update.find(_rule.first) != _update.end()) && (_update.find(_rule.second) != _update.end())) {
        // Check if the middle page is in the rule, and update it accordingly.
        if (_middle_page == _rule.first) {
            _middle_page = _rule.second;
        } else if (_middle_page == _rule.second) {
            _middle_page = _rule.first;
        }
        // Switch the position of both pages.
        temp = _update[_rule.first];
        _update[_rule.first] = _update[_rule.second];
        _update[_rule.second] = temp;
    }
    // Return.
    return 0;
}
int PrintQueue::checkUpdates(
    std::vector<std::pair<std::unordered_map<int, int>, int>>& _updates,
        std::vector<std::pair<int, int>> _rules, int& _result, int& _result_fixed) {
    // Initialize function variables.
    _result = 0;
    _result_fixed = 0;
    bool flag;
    // Iterate through each update.
    for (int i = 0; i < _updates.size(); i++) {
        // Reset the flag.
        flag = true;
        // Iterate through each rules.
        for (int j=0; j < _rules.size(); j++) {
            // Check if the update is valid.
            if (!this->isUpdateValid(_updates[i].first, _rules[j])) {
                // We try to fix the update
                this->fixUpdate(_updates[i].first, _rules[j], _updates[i].second);
                // If not, we set the validation flag to false.
                flag = false;
                // And we reset the loop to make sure the change didn't break any other rule.
                j = 0;
            }
        }
        // If everything was fine, we add its middle page index to the result.
        if (flag) {
             _result += _updates[i].second;
        } else {
            std::cout << _updates[i].second << std::endl;
            _result_fixed += _updates[i].second;
        }
    }
    // Log the result.
    std::cout << "The sum of middle pages of valid updates is : " << _result << std::endl;
    std::cout << "The sum of middle pages of previously invalid updates is : " << _result_fixed << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> ACCESSERS
//> GETTERS
//> SETTERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
