/**
 * @file guard_gallivant.hpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the header of the Guard Gallivant problem proposed in Day 6 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

#ifndef _DAY_6_GUARD_GALLIVANT_HPP_
#define _DAY_6_GUARD_GALLIVANT_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///> DEPENDENCIES
//> C/C++ libraries
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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
//> STRUCTS DECLARATION
struct PairHash {
    /**
     * @brief Hash declaration for std::pair<int, int>.
     *
     * This struct provides a hash function for pairs of integers, suitable for use
     * with unordered containers such as std::unordered_map or std::unordered_set.
     * The hash is computed by hashing each element of the pair individually and
     * then combining the results using a bitwise operation.
     *
     * @note The hash combination method used here is similar to boost::hash_combine.
     */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /**
     * @brief Hash function for std::pair<int, int>.
     *
     * Computes a hash value for a pair of integers by combining the hashes of the individual elements.
     * This is useful for using std::pair<int, int> as a key in hash-based containers like std::unordered_map.
     *
     * @param p The pair of integers to hash.
     * @return The computed hash value.
     */
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);
        return h1 ^ (h2 << 1);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

struct Guard {
    /**
     * @struct Guard
     * @brief Represents a guard entity that tracks its current position, orientation, and all unique cells it has occupied.
     *
     * The Guard struct maintains the following information:
     * - current_position_: The current coordinates of the guard on the grid.
     * - previous_positions_: An unordered set containing all unique positions (cells) the guard has previously occupied.
     * - current_orientation_: The current orientation of the guard, represented as a pair of integers.
     */

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> ATTRIBUTES
    //> DYNAMIC / They can change during runtime.
    /**
     * @brief Represents a pair of integer values, typically used to store coordinates or positions.
     * 
     * The first element corresponds to the x-coordinate, and the second element corresponds to the y-coordinate.
     */
    std::pair<int, int> current_position_ = std::pair<int, int>{0, 0};
    /**
     * @brief A set of pairs representing all unique positions the guard has occupied.
     *
     * This unordered_set allows for efficient tracking of previously visited cells,
     * ensuring that each position is stored only once, regardless of how many times
     * the guard has visited it.
     */
    std::unordered_set<std::pair<int, int>, PairHash> previous_positions_;
    /**
     * @brief The current orientation of the guard, represented as a pair of integers.
     *
     * This pair indicates the direction in which the guard is currently facing or moving.
     * The first element typically represents the vertical direction (up/down), and the second
     * element represents the horizontal direction (left/right).
     */
    std::pair<int, int> current_orientation_ = std::pair<int, int>{0, 0};
    /**
     * @brief The number of turns the guard has made.
     *
     * This integer keeps track of how many times the guard has changed its orientation
     * while navigating through the grid. It can be used to analyze the guard's movement patterns.
     */
    int nb_turn_ = 0;
    int nb_obstructions_ = 0;
    std::vector<std::pair<int, int>> previous_obstacles_ = {};
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

///> CLASS DECLARATION
class GuardGallivant : public BaseAdventDay {
/**
 * @class GuardGallivant
 * @brief A class to process the Advent of Code Day 4 problem.
 *
 * Inherits from BaseAdventDay. This class loads a character grid, computes hashes,
 * searches for words or patterns, and tracks occurrences using custom logic.
 */

 public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> CONSTRUCTORS
    /**
     * @brief Constructor of the class. Declared as explicit to prevent ambiguous instantiation.
     * @param _filename Path to the input file.
     */
    explicit GuardGallivant(std::string _filename);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> DESTRUCTORS
    /**
     * @brief Destructor of the class.
     */
    ~GuardGallivant();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///> FUNCTIONS
    /**
     * @brief Declare a run function to comply with the base class.
     * @return int Returns 0 on success, or a non-zero error code on failure.
     */
    int run();
    /**
     * @brief Loads map data from a file into a 2D character vector.
     *
     * Reads the contents of the specified file and populates the provided
     * vector of vectors with the map data, where each inner vector represents
     * a row of characters from the file.
     * The time complexity of this function is O(n), where n is the number of characters in the file.
     * The space complexity is O(n), where n is the number of characters in the file,
     *
     * @param _fn The path to the file containing the map data.
     * @param _map Reference to a 2D vector to be filled with the map data.
     * @return int Returns 0 on success, or a non-zero error code on failure.
     */
    int loadDataFromFile(
      const std::string& _fn, std::vector<std::vector<char>>& _map);
    /**
     * @brief Initializes the guards on the map and sets their orientations.
     *
     * This function processes the provided map to locate guards, initializes
     * their positions and states in the _guards vector, and updates the
     * _orientations map with each guard's orientation.
     * 
     * The time complexity of this function is O(n), where n is the size of the map.
     * The space complexity is O(g), where g is the number of guards found on the map, where g <= n.
     *
     * @param _map Reference to a 2D vector representing the map layout.
     * @param _guards Reference to a vector where Guard objects will be initialized.
     * @param _orientations Reference to an unordered_map mapping guard identifiers
     *        (char) to their orientation as a pair of coordinates (row, col).
     * @return int The number of guards successfully initialized.
     */
    int inititializeGuards(
       std::vector<std::vector<char>>& _map, std::vector<Guard>& _guards,
          std::unordered_map<char, std::pair<int, int>>& _orientations);
    /**
     * @brief Moves all guards on the map according to their movement logic.
     *
     * This function updates the positions of the guards in the provided vector
     * based on the current state of the map. The movement logic for each guard
     * is determined by their individual properties and the layout of the map.
     * 
     * The time complexity of this function is O(g * m), where g is the number of guards and m However, it should be noted that the guard could theoretically be stuck in a loop forever,  is the maximum number of moves a guard can make before exiting the map.
     * It can theoritically run forever if the guards are stuck in a loop, so the time complexity is not strictly bounded.
     * The space complexity is O(1).
     *
     * @param _map A reference to a 2D vector representing the map grid.
     *             Each cell contains a character indicating its type or state.
     * @param _guards A reference to a vector of Guard objects to be moved.
     * @return The function returns 0 on success, or a non-zero error code on failure.
     */
    int moveGuards(
        std::vector<std::vector<char>>& _map, std::vector<Guard>& _guards);
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
     * @brief The map of the laboratory. Each element is a char representing the state of the cell.
     */
    std::vector<std::vector<char>> map_;
    /**
      * @brief The list of guards strolling the map.
     */
    std::vector<Guard> guards_;
    /**
     * @brief Maps orientation characters to their corresponding movement vectors.
     */
    std::unordered_map<char, std::pair<int, int>> orientations_ = {
        {'^', {-1, 0}},
        {'v', {1, 0}},
        {'>', {0, 1}},
        {'<', {0, -1}}
    };
    //> FIXED / They cannot change during runtime. Declared as const.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // _DAY_6_GUARD_GALLIVANT_HPP_

