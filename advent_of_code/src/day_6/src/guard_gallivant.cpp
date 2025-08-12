/**
 * @file guard_gallivant.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the source of the Guard Gallivant problem proposed in Day 6 of the Advent of Code.
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
#include <unordered_set>
#include <utility>
#include <vector>
//> Custom-made libraries
#include <day_6/guard_gallivant.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> CONSTRUCTORS
GuardGallivant::GuardGallivant(std::string _filename) :
    BaseAdventDay(_filename) {
    //> INITIALIZING EVERY ATTRIBUTE.
    this->map_ = std::vector<std::vector<char>>{};
    this->guards_ = std::vector<Guard>{};
    //> LOGGING.
    std::cout << "GuardGallivant initialized with file: " << this->filename_ << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DESTRUCTORS
GuardGallivant::~GuardGallivant() {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> FUNCTIONS
int GuardGallivant::run() {
    // Load data from file.
    if (this->loadDataFromFile(this->filename_, this->map_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error loading data from file: " << this->filename_ << std::endl;
        // And return an error code.
        return 1;
    }
    // Initialize guards.
    if (this->inititializeGuards(this->map_, this->guards_, this->orientations_)) {
        // If there was an error initializing the guards, log it.
        std::cerr << "Error initializing guards." << std::endl;
        // And return an error code.
        return 1;
    }
    // Run the loop that will move the guards.
    if (this->moveGuards(this->map_, this->guards_)) {
        // If there was an error moving the guards, log it.
        std::cerr << "Error moving guards." << std::endl;
        // And return an error code.
        return 2;
    }
    // Log the final number of move of the guards.
    std::cout << "Total number of guards: " << this->guards_.size() << std::endl;
    for (const auto& guard : this->guards_) {
        std::cout << "Guard made " << guard.previous_positions_.size() << " moves, with " << guard.nb_turn_ << " turns." << std::endl;
        std::cout << "We can place " << guard.nb_obstructions_ << " obstructions to block him." << std::endl;
    }
    // Return success.
    return 0;
}
int GuardGallivant::loadDataFromFile(
    const std::string& _fn, std::vector<std::vector<char>>& _map) {
    // Initialize the function variables.
    std::string line;
    int index = 0;
    // Reset the report map.
    _map.clear();
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
        // Add a new line to the grid.
        _map.push_back({});
        // Iterate thourgh each character in the line.
        for (const char& c : line) {
            // If the character is not a space, add it to the grid.
            _map[index].push_back(c);
        }
        // Update the line index.
        index += 1;
    }
    // Display the loaded grid.
    std::cout << "Loaded grid from file: " << _fn << std::endl;
    for (const auto& row : _map) {
        for (const char& c : row) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    // Close the file.
    file.close();
    // Return.
    return 0;
}
int GuardGallivant::inititializeGuards(
    std::vector<std::vector<char>>& _map, std::vector<Guard>& _guards,
        std::unordered_map<char, std::pair<int, int>>& _orientations) {
    // Iterate though the map.
    for (int i=0; i < _map.size(); ++i) {
        for (int j=0; j < _map[i].size(); ++j) {
            // If the cell is a guard, initialize it.
            if (_orientations.find(_map[i][j]) != _orientations.end()) {
                // Log the guard initialization.
                std::cout << "Guard found at position (" << i << ", " << j << ")." << std::endl;
                // Add the guard to the guards vector.
                _guards.emplace_back();
                // Set the guard's initial position.
                _guards.back().current_position_ = std::make_pair(i, j);
                // Update the guard's previous positions.
                _guards.back().previous_positions_.insert(_guards.back().current_position_);
                // Set the guard's orientation.
                _guards.back().current_orientation_ = _orientations[_map[i][j]];
            }
        }
    }
    // Return.
    return 0;
}
int GuardGallivant::moveGuards(std::vector<std::vector<char>>& _map, std::vector<Guard>& _guards) {
      // Initialize the flag to check if all guards have exited the map.
    bool is_any_guard_left = true;
    // While not all guards have exited the map.
    while (is_any_guard_left) {
        // Reset the flag to false.
        is_any_guard_left = false;
        // Iterate over each guard and make them move.
        for (auto& guard : this->guards_) {
            // If the guard's current orientation is not null, move the guard.
            if (guard.current_orientation_ != std::make_pair(0, 0)) {
                // Update the flag.
                is_any_guard_left = true;
                // Check the content of the next cell.
                int next_row = guard.current_position_.first + guard.current_orientation_.first;
                int next_col = guard.current_position_.second + guard.current_orientation_.second;
                // If the next cell is within bounds.
                if (next_row >= 0 && next_row < this->map_.size() &&
                    next_col >= 0 && next_col < this->map_[next_row].size()) {
                    // If the next cell is a wall, rotate the guard.
                    if (this->map_[next_row][next_col] == '#') {
                        // Increase the number of turns made by the guard.
                        guard.nb_turn_ += 1;
                        // Register the obstruction.
                        guard.previous_obstacles_.push_back(std::make_pair(next_row, next_col));
                        // Log the registry.
                        std::cout << "Guard registered an obstruction at (" << next_row << ", " << next_col << ")." << std::endl;
                        // Rotate the guard's orientation.
                        if (guard.current_orientation_ == std::make_pair(0, -1)) {
                            guard.current_orientation_ = std::make_pair(-1, 0);  // Rotate right
                        } else if (guard.current_orientation_ == std::make_pair(1, 0)) {
                            guard.current_orientation_ = std::make_pair(0, -1);  // Rotate down
                        } else if (guard.current_orientation_ == std::make_pair(0, 1)) {
                            guard.current_orientation_ = std::make_pair(1, 0);  // Rotate left
                        } else if (guard.current_orientation_ == std::make_pair(-1, 0)) {
                            guard.current_orientation_ = std::make_pair(0, 1);  // Rotate up
                        }
                        // If the nb of turns is greater or equal to 3, we check if we can place an obstruction.
                        if (guard.previous_obstacles_.size() >= 3) {
                            std::pair<int, int> check_obstacle = guard.current_position_;
                            std::pair<int, int> target_obstacle = guard.current_position_;
                            if (guard.current_orientation_ == std::make_pair(0, -1)) {
                                target_obstacle.second = guard.previous_obstacles_[guard.nb_turn_ - 3].second - 1;
                            } else if (guard.current_orientation_ == std::make_pair(1, 0)) {
                                target_obstacle.first = guard.previous_obstacles_[guard.nb_turn_ - 3].first + 1;
                            } else if (guard.current_orientation_ == std::make_pair(0, 1)) {
                                target_obstacle.second = guard.previous_obstacles_[guard.nb_turn_ - 3].second + 1;
                            } else if (guard.current_orientation_ == std::make_pair(-1, 0)) {
                                target_obstacle.first = guard.previous_obstacles_[guard.nb_turn_ - 3].first - 1;
                            }
                            bool can_place_obstruction = true;
                            // We need to check each cell between the guard current position, the cell where we want to place the obstruction,
                            // And the cell two turns before, to see if they all connect without any "natural" obstruction.
                            // for (int i = check_obstacle.first; i < guard.previous_obstacles_[guard.nb_turn_ - 2].first; i++) {
                            //     for (int j = check_obstacle.second; j < guard.previous_obstacles_[guard.nb_turn_ - 2].second; j++) {
                            //         // If there are no obstacle on the way, we can put an obstruction.
                            //         if (this->map_[i][j] == '#') can_place_obstruction = false;
                            //     }
                            // } // NEED TO BETTER IMPLEMENT THIS.               
                            // If we can place an obstruction, we increase the number of obstructions.
                            if (can_place_obstruction) {
                                // Increase the number of obstructions.
                                guard.nb_obstructions_ += 1;
                                // Log the placement of the obstruction.
                                std::cout << "Placing an obstruction at (" << target_obstacle.first << ", " << target_obstacle.second << ")." << std::endl;
                            }
                        }
                        // Continue to the next guard.
                        continue;
                    } else {
                        // Move the guard to the next cell.
                        guard.current_position_ = std::make_pair(next_row, next_col);
                        // Log the guard's movement.
                        std::cout << "Guard moved to position (" << guard.current_position_.first << ", "
                                << guard.current_position_.second << ") with orientation ("
                                << guard.current_orientation_.first << ", "
                                << guard.current_orientation_.second << ")." << std::endl;
                        // Then, update the guard's previous positions.
                        guard.previous_positions_.insert(guard.current_position_);
                    }
                } else {
                    // Set the orientation to null.
                    guard.current_orientation_ = std::make_pair(0, 0);
                    // Log the guard's orientation change.
                    std::cout << "Guard exited the map." << std::endl;
                }
            }
        }
    }
    // Return success.
    std::cout << "All guards have exited the map." << std::endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> ACCESSERS
//> GETTERS
//> SETTERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
