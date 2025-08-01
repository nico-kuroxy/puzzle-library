/**
 * @file main.cpp
 * @author nicolas.erbetti.k@gmail.com
 * @brief This file defines the executable of the Historian Hysteria problem proposed in Day 1 of the Advent of Code.
 * @copyright © 2025 Nicolas Erbetti
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <iostream>
//> Custom-made libraries
#include <day_1/historian_hysteria.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> EXECUTABLE
/* Main function of the executable running the code. */
int main(int argc, char **argv) {
    // Log.
    std::cout << "Initialiazing the distance list problem..." << std::endl;
    // Check the arguments.
    if (argc < 2) {
        std::cerr << argv[0] << ": You are missing the path to the data file. Add it to the command line." << std::endl;
        return 1;
    }
    // Initialize the class.
    HistorianHysteria historian_hysteria(argv[1]);
    // Run the code.
    historian_hysteria.run();
    // Log.
    std::cout << "Exiting the program." << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
