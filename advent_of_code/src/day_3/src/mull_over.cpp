/**
 * @file mull_over.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the source of the Mull it Over problem proposed in Day 3 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
//> Custom-made libraries
#include <day_3/mull_over.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> CONSTRUCTORS
MullOver::MullOver(std::string _filename) :
    BaseAdventDay(_filename) {
    //> INITIALIZING EVERY ATTRIBUTE.
    this->memory_ = "";
    this->result_ = 0;
    this->result_instructions_ = 0;
    this->mul_enabled_ = true;
    //> LOGGING.
    std::cout << "MullOver initialized with file: " << this->filename_ << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DESTRUCTORS
MullOver::~MullOver() {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> FUNCTIONS
int MullOver::run() {
    // Load data from file.
    if (this->loadDataFromFile(this->filename_, this->memory_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error loading data from file: " << this->filename_ << std::endl;
        // And return an error code.
        return 1;
    }
    if (this->multiplyMemory(this->memory_, this->result_, this->result_instructions_, this->mul_enabled_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error multiplying over the memory." << std::endl;
        // And return an error code.
        return 2;
    }
    // Return success.
    return 0;
}
int MullOver::loadDataFromFile(const std::string& _fn, std::string& _memory) {
    // Initialize the function variables.
    std::string line;
    // Reset the memory.
    _memory = "";
    // Try to open the file.
    std::ifstream file(_fn);
    // If the file could not be opened, return an error.
    if (!file) {
        // Log the error.
        std::cerr << "Failed to open file." << std::endl;
        // Return.
        return 1;
    }
    // Read the file line by line and store the data.
    while (std::getline(file, line)) {
        // Add the line to the memory.
        _memory += line;
    }
    std::cout << "Data loaded from file: " << _fn << std::endl;
    // Close the file.
    file.close();
    // Return.
    return 0;
}
int MullOver::multiplyMemory(const std::string& _memory, int& _result, int& _result_instructions, bool& _mul_enabled) {
    // Initialize function variables.
    std::regex mul_regex(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    std::smatch match;
    int x, y;
    // Reset the result.
    _result = 0;
    _result_instructions = 0;
    // Iterate over the memory string.
    std::string::const_iterator search_start(_memory.cbegin());
    // Find the first occurence of "mul(x,y)" and continue until the end
    while (std::regex_search(search_start, _memory.cend(), match, mul_regex)) {
        // Check if the match is for the do() or don't() pattern
        if (match[0] == "do()") {
            // Enable multiplication.
            _mul_enabled = true;
        } else if (match[0] == "don't()") {
            // Disable multiplication.
            _mul_enabled = false;
        } else if (match[1].matched && match[2].matched) {
            // Check if the match is for the mul(x, y) pattern
            // Fmi, match[0] is the full match, match[1] is the first capture group, and match[2] the second.
            x = std::stoi(match[1]);
            y = std::stoi(match[2]);
            // Multiply them and add the result.
            _result += (x * y);
            // Same if mul if enabled.
            if (_mul_enabled) _result_instructions += (x * y);
        }
        // Advance search position
        search_start = match.suffix().first;
    }
    // Log the result.
    std::cout << "Result of multiplication: " << _result << std::endl;
    std::cout << "Result of multiplication with instructions: " << _result_instructions << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> ACCESSERS
//> GETTERS
//> SETTERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
