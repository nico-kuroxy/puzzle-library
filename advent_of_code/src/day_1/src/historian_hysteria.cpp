/**
 * @file historian_hysteria.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the source of the Historian Hysteria problem proposed in Day 1 of the Advent of Code.
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
#include <day_1/historian_hysteria.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> CONSTRUCTORS
HistorianHysteria::HistorianHysteria(std::string _filename) :
    BaseAdventDay(_filename) {
    //> INITIALIZING EVERY ATTRIBUTE.
    this->data_l_ = std::vector<int>();
    this->data_r_ = std::vector<int>();
    this->distance_ = 0;
    this->similarity_ = 0;
    this->similarity_map_ = std::unordered_map<int, std::pair<int, int>>();
    //> LOGGING.
    std::cout << "HistorianHysteria initialized with file: " << this->filename_ << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DESTRUCTORS
HistorianHysteria::~HistorianHysteria() {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> FUNCTIONS
int HistorianHysteria::run() {
    // Load data from file.
    if (this->loadDataFromFile(this->filename_, this->data_l_, this->data_r_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error loading data from file: " << this->filename_ << std::endl;
        // And return an error code.
        return 1;
    }
    // Process the data.
    if (this->computeDistance(this->data_l_, this->data_r_, this->distance_)) {
        // If there was an error computing the dustance, log it.
        std::cerr << "Error computing the distance." << std::endl;
        // And return an error code.
        return 2;
    }
    // Find the similarity.
    if (this->computeSimilarity(this->data_l_, this->data_r_, this->similarity_, this->similarity_map_)) {
        // If there was an error computing the dustance, log it.
        std::cerr << "Error computing the similarity." << std::endl;
        // And return an error code.
        return 3;
    }
    // Return success.
    return 0;
}
int HistorianHysteria::loadDataFromFile(const std::string& _fn, std::vector<int>& _data_l, std::vector<int>& _data_r) {
    // Initialize the function variables.
    int left_id, right_id, extra;
    std::string line;
    // Reset the data vectors.
    _data_l.clear();
    _data_r.clear();
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
        // Assuming each line contains two ids, separated by spaces.
        std::istringstream iss(line);
        // Try to read the two ids from the line.
        if (iss >> left_id >> right_id) {
            // Check if there is any extra data in the line after the two ids.
            if (iss >> extra) {
                // There is more data after the two expected tokens
                std::cerr << "Invalid line: " << line << ". Only two space-separated IDs are expected." << std::endl;
                // Return.
                return 2;
            }
            // Check if both ids are positive integers.
            if (left_id < 0 || right_id < 0) {
                // If not, print an error message.
                std::cerr << "Error: [" << left_id << ", " << right_id << "] must be positive integers." << std::endl;
                // And return an error code.
                return 3;
            }
            // Add the ids to the respective vectors.
            _data_l.push_back(left_id);
            _data_r.push_back(right_id);
        } else {
            // If the line does not contain two ids, print an error message.
            std::cerr << "Invalid line: " << line << ". Two space-separated IDs are expected." << std::endl;
            // And return an error code
            return 4;
        }
    }
    // Close the file.
    file.close();
    // Return.
    return 0;
}
int HistorianHysteria::computeDistance(std::vector<int>& _data_l, std::vector<int>& _data_r, int& _distance) {
    // Check if the two vectors have the same size.
    if (_data_l.size() != _data_r.size()) {
        // If not, print an error message and return an error code.
        std::cerr << "Error: The left and right data vectors must have the same size." << std::endl;
        // Return.
        return 1;
    }
    // Initialize the function variables.
    _distance = 0;
    // Sort the vectors.
    std::sort(_data_l.begin(), _data_l.end());
    std::sort(_data_r.begin(), _data_r.end());
    // Iterate over the vectors.
    for (size_t i = 0; i < _data_l.size(); i++) {
        // Check if both ids are positive integers.
        if (_data_l[i] < 0 || _data_r[i] < 0) {
            // If not, print an error message.
            std::cerr << "Error: [" << _data_l[i] << ", " << _data_r[i] << "] must be positive integers." << std::endl;
            // And return an error code.
            return 2;
        }
        // Compute the distance between the left and right ids.
        _distance += std::abs(_data_l[i] - _data_r[i]);
    }
    // Log the final computer distance.
    std::cout << "Computed distance: " << _distance << std::endl;
    // Return.
    return 0;
}
int HistorianHysteria::computeSimilarity(
    std::vector<int>& _data_l, std::vector<int>& _data_r,
        int& _similarity, std::unordered_map<int, std::pair<int, int>>& _similarity_map) {
    // Check if the two vectors have the same size.
    if (_data_l.size() != _data_r.size()) {
        // If not, print an error message and return an error code.
        std::cerr << "Error: The left and right data vectors must have the same size." << std::endl;
        // Return.
        return 1;
    }
    // Initialize the function variables.
    _similarity = 0;
    _similarity_map.clear();
    // Iterate over the left ids.
    for (const auto& id : _data_l) {
        // Check if the id is a positive integer.
        if (id < 0) {
            // If not, print an error message.
            std::cerr << "Error: " << id << " must be a positive integer." << std::endl;
            // And return an error code.
            return 2;
        }
        // Check if the id is already in the similarity map.
        if (_similarity_map.find(id) == _similarity_map.end()) {
            // If it is not, initialize its count in the left list.
            _similarity_map[id].first = 1;
            // And initialize its count in the right list to 0.
            _similarity_map[id].second = 0;
        } else {
            // And if it is, increment its count in the left map.
            _similarity_map[id].first++;
        }
    }
    // Now, iterate over the right ids.
    for (const auto& id : _data_r) {
        // Check if the id is a positive integer.
        if (id < 0) {
            // If not, print an error message.
            std::cerr << "Error: " << id << " must be a positive integer." << std::endl;
            // And return an error code.
            return 3;
        }
        // Check if the id is in the similarity map.
        if (_similarity_map.find(id) != _similarity_map.end()) {
            // If it is, increment its count in the second element of the pair.
            _similarity_map[id].second++;
        }
    }
    // Iterate over the similarity map, now that is fully populated.
    for (const auto& it : _similarity_map) {
        // Update the similarity score as the product between the id, its left list count and its right list count.
        _similarity += it.first * it.second.first * it.second.second;
    }
    // Log the final computer similarity.
    std::cout << "Computed similarity: " << _similarity << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> ACCESSERS
//> GETTERS
//> SETTERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
