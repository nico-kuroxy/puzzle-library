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
    this->new_pages_ = {};
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
    if (this->loadDataFromFile(this->filename_, this->page_rules_, this->new_pages_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error loading data from file: " << this->filename_ << std::endl;
        // And return an error code.
        return 1;
    }
    // Return success.
    return 0;
}
int PrintQueue::loadDataFromFile(
    const std::string& _fn, std::vector<std::pair<int, int>>& _page_rules, std::vector<int> _new_pages) {
    // Initialize the function variables.
    std::string line, first_page_str, second_page_str, extra_page_str;
    int first_page, second_page, extra_page;
    bool are_rules_registered = false;
    // Reset the page variables.
    _page_rules.clear();
    _new_pages.clear();
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
            // Otherwise, we add the pages.
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
                _new_pages.push_back(extra_page);
            }
        }
    }
    // Display the loaded rules.
    std::cout << "Loaded rules from file: " << _fn << std::endl;
    for (const auto& rule : _page_rules) {
        std::cout << rule.first << " | " << rule.second << std::endl;
    }
    // Display the loaded pages.
    std::cout << "Loaded pages from file: " << _fn << std::endl;
    for (const int& page : _new_pages) {
        std::cout << page << ", ";
    }
    std::cout << std::endl;
    // Close the file.
    file.close();
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> ACCESSERS
//> GETTERS
//> SETTERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
