/**
 * @file main.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the executable of the Guard Gallivant problem proposed in Day 6 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <iostream>
//> Custom-made libraries
#include <day_6/guard_gallivant.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> EXECUTABLE
/* Main function of the executable running the code. */
int main(int argc, char **argv) {
    // Log.
    std::cout << "Initialiazing the print queue problem..." << std::endl;
    // Check the arguments.
    if (argc < 2) {
        std::cerr << argv[0] << ": You are missing the path to the data file. Add it to the command line." << std::endl;
        return 1;
    }
    // Initialize the class.
    GuardGallivant guard_gallivant(argv[1]);
    // Run the code.
    guard_gallivant.run();
    // Log.
    std::cout << "Exiting the program." << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
