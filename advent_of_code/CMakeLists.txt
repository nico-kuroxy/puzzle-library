cmake_minimum_required(VERSION 3.14)
project(advent_of_code LANGUAGES CXX)


#########################
## Compilation options ##
#########################

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 17)
# Set default output directories.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

####################
## Subdirectories ##
####################

# Add subdirectories for each day's code.
# This assumes each day has its own CMakeLists.txt file.
add_subdirectory(src/day_1)
add_subdirectory(src/day_2)
add_subdirectory(src/day_3)
add_subdirectory(src/day_4)

