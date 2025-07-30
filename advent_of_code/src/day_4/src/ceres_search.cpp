/**********************************************************************************************************************/
//   author: nicolas.erbetti.k@gmail.com
//   brief: This file defines the source of the Ceres Search problem proposed in the day 4 of the advent of code.
//   copyright: © 2025 Nicolas Erbetti.
/**********************************************************************************************************************/

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
#include <day_4/ceres_search.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> CONSTRUCTORS
CeresSearch::CeresSearch(std::string _filename) {
    //> INITIALIZING EVERY ATTRIBUTE.
    this->filename_ = _filename;
    this->grid_ = {};
    this->nb_found_ = 0;
    this->nb_xmas_found_ = 0;
    //> LOGGING.
    std::cout << "CeresSearch initialized with file: " << this->filename_ << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DESTRUCTORS
CeresSearch::~CeresSearch() {
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> FUNCTIONS
int CeresSearch::run(std::string _word, std::string _pattern) {
    // Load data from file.
    if (this->loadDataFromFile(this->filename_, this->grid_)) {
        // If there was an error loading the data, log it.
        std::cerr << "Error loading data from file: " << this->filename_ << std::endl;
        // And return an error code.
        return 1;
    }
    // Count the words in the grid.
    if (this->countWords(this->grid_, this->directions_, _word, this->nb_found_, this->BASE, this->MOD)) {
        // If there was an error counting the words, log it.
        std::cerr << "Error counting words in the grid." << std::endl;
        // And return an error code.
        return 1;
    }
    // Count the cross patterns in the grid.
    if (this->countPattern(this->grid_, this->dir_branch_1_, this->dir_branch_2_, this->nb_xmas_found_, _pattern)) {
        // If there was an error counting the XMAS patterns, log it.
        std::cerr << "Error counting XMAS patterns in the grid." << std::endl;
        // And return an error code.
        return 2;
    }
    // Return success.
    return 0;
}
int CeresSearch::loadDataFromFile(const std::string& _fn, std::vector<std::vector<char>>& _grid) {
    // Initialize the function variables.
    std::string line;
    int index = 0;
    // Reset the report map.
    _grid.clear();
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
        _grid.push_back({});
        // Iterate thourgh each character in the line.
        for (const char& c : line) {
            // If the character is not a space, add it to the grid.
            _grid[index].push_back(c);
        }
        // Update the line index.
        index += 1;
    }
    // Display the loaded grid.
    std::cout << "Loaded grid from file: " << _fn << std::endl;
    for (const auto& row : _grid) {
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
int CeresSearch::countWords(
    const std::vector<std::vector<char>>& _grid, const std::vector<std::pair<int, int>>& _directions,
        const std::string& _word, int& _nb_found, const uint64_t& _BASE, const uint64_t& _MOD) {
    // Initialize the function variables.
    int nb_rows = _grid.size();
    int nb_cols = _grid.empty() ? 0 : _grid[0].size();
    int size_word = _word.size();
    // Reset the number of words found.
    _nb_found = 0;
    // Precompute the hash of the word to search for.
    uint64_t word_hash = compute_hash(_word, _BASE, _MOD);
    uint64_t pow_base = 1;
    for (int i = 1; i < size_word; i++) pow_base = (pow_base * _BASE) % _MOD;
    // Check if the grid is ill-formed.
    for (int i=0; i < nb_rows; i++) {
        // Check if each row has the same number of columns.
        if (_grid[i].size() != nb_cols) {
            // Log the error.
            std::cerr << "Error: Grid is not well-formed at row [" << i << std::endl;
            // Return an error code.
            return 1;
        }
    }
    // Iterate through the whole grid to search for the first letter of the word.
    for (int i = 0; i < nb_rows; ++i) {
        for (int j = 0; j < nb_cols; ++j) {
            // Only consider positions matching first character of word.
            if (_grid[i][j] == _word[0]) {
                // Extract the direction parameters.
                for (const auto& [dx, dy] : _directions) {
                    // Check if the word fits in the current direction.
                    int end_i = i + dx * (size_word - 1);
                    int end_j = j + dy * (size_word - 1);
                    if (end_i < 0 || end_j < 0 || end_i >= nb_rows || end_j >= nb_cols) {
                        // If the end position is out of bounds, skip this direction.
                        continue;
                    }
                    // Build string and compute hash on the fly.
                    uint64_t h = 0;
                    // Compute the hash for the current direction.
                    for (int k = 0; k < size_word; ++k) {
                        int ni = i + dx * k;
                        int nj = j + dy * k;
                        h = (h * _BASE + _grid[ni][nj]) % _MOD;
                    }
                    // Check if the computed hash matches the word hash.
                    if (h == word_hash) {
                        // If the hashes match, we found the word.
                        _nb_found += 1;
                    }
                }
            }
        }
    }
    // Log the numbers of words found.
    std::cout << "Found " << _nb_found << " occurrences of the word '" << _word << "' in the grid." << std::endl;
    // Return.
    return 0;
}
uint64_t CeresSearch::compute_hash(const std::string& _word, const uint64_t& _BASE, const uint64_t& _MOD) {
    // Initialize the hash value.
    uint64_t h = 0;
    // Iterate through each character in the string.
    for (char c : _word) {
        // Multiply current hash by BASE and add the character, then take modulo MOD
        h = (h * _BASE + c) % _MOD;
    }
    return h;
}
int CeresSearch::countPattern(
    const std::vector<std::vector<char>>& _grid, const std::vector<std::pair<int, int>>& _dir_branch_1,
         const std::vector<std::pair<int, int>>& _dir_branch_2, int& _nb_xmas_found, std::string _pattern) {
    // Check if the pattern is valid.
    if (_pattern.size() != 3) {
        // Log the error.
        std::cerr << "Error: Invalid pattern size. The pattern must be of size 3." << std::endl;
        // Return an error code.
        return 1;
    }
    // Initialize the function variables.
    int nb_rows = _grid.size();
    int nb_cols = _grid.empty() ? 0 : _grid[0].size();
    // Reset the number of patterns found.
    _nb_xmas_found = 0;
    // Prepare patterns to search for.
    std::string rev_pattern = _pattern;
    std::reverse(rev_pattern.begin(), rev_pattern.end());
    std::vector<std::string> patterns = {_pattern, rev_pattern};
    // Helper lambda to check if a sequence of cells matches one of the patterns.
    auto matches_pattern =
        [&](const std::vector<std::pair<int, int>>& coords, int _grid_center_x, int _grid_center_y) -> bool {
        // Initialize the coordinates.
        int x, y;
        // Initialize the sequence.
        std::string seq;
        // Iterate through the coordinates and build the sequence.
        for (auto [dx, dy] : coords) {
            // Build the sequence.
            x = _grid_center_x + dx;
            y = _grid_center_y + dy;
            if (x < 0 || y < 0 || x >= nb_rows || y >= nb_cols) return false;
            seq.push_back(_grid[x][y]);
        }
        // Check if the sequence matches any of the patterns.
        for (const auto& p : patterns) {
            if (seq == p) return true;
        }
        return false;
    };
    // Iterate through the whole rid.
    for (int i = 1; i < nb_rows - 1; ++i) {
        for (int j = 1; j < nb_cols - 1; ++j) {
            // Check the first branch.
            bool first_ok = matches_pattern(_dir_branch_1, i, j);
            // Check the second branch.
            bool second_ok = matches_pattern(_dir_branch_2, i, j);
            // If we found both branches...
            if (first_ok && second_ok) {
                // Increment the count.
                _nb_xmas_found += 1;
            }
        }
    }
    // Log the number of XMAS patterns found.
    std::cout << "Found " << _nb_xmas_found << " " << _pattern << " patterns in the grid." << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> ACCESSERS
//> GETTERS
//> SETTERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
