/**
 * @file main.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the executable of the Mull it Over problem proposed in Day 3 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <iostream>
//> Custom-made libraries
#include <day_3/mull_over.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> EXECUTABLE
/* Main function of the executable running the code. */
int main(int argc, char **argv) {
    // Log.
    std::cout << "Initialiazing the mull it over problem..." << std::endl;
    // Check the arguments.
    if (argc < 2) {
        std::cerr << argv[0] << ": You are missing the path to the data file. Add it to the command line." << std::endl;
        return 1;
    }
    // Initialize the class.
    MullOver mull_over(argv[1]);
    // Run the code.
    mull_over.run();
    // Log.
    std::cout << "Exiting the program." << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
