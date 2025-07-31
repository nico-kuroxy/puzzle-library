/**********************************************************************************************************************/
//   author: nicolas.erbetti.k@gmail.com
//   brief: This file defines the executable of the Ceres Search problem
//          proposed in the day 4 of the advent of code.
//   copyright: © 2025 Nicolas Erbetti.
/**********************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> DEPENDENCIES
//> C/C++ libraries
#include <iostream>
//> Custom-made libraries
#include <day_4/ceres_search.hpp>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//> EXECUTABLE
/* Main function of the executable running the code. */
int main(int argc, char **argv) {
    // Log.
    std::cout << "Initialiazing the ceres search problem..." << std::endl;
    // Check the arguments.
    if (argc < 4) {
        std::cerr << argv[0] << ": You are missing the path to the data file. Add it to the command line." << std::endl;
        std::cerr << argv[0] << ": You also need to specify the word you are looking for. Eg. 'XMAS'." << std::endl;
        std::cerr << argv[0] << ": You also need to specify the pattern you are looking for. Eg. 'MAS'." << std::endl;
        return 1;
    }
    // Initialize the class.
    CeresSearch ceres_search(argv[1]);
    // Run the code.
    ceres_search.run(argv[2], argv[3]);
    // Log.
    std::cout << "Exiting the program." << std::endl;
    // Return.
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
