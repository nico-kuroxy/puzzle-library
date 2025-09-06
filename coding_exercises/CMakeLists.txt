cmake_minimum_required(VERSION 3.14)
project(coding_exercise LANGUAGES CXX)

#########################
## Compilation options ##
#########################

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 17)
# Set default output directories.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#############
## Testing ##
#############

# Enable CMakeLists testing, need to be set in the top CMakeLists.
enable_testing()

####################
## Subdirectories ##
####################

# Add subdirectories for each package's code.
# This assumes each has its own CMakeLists.txt file.
add_subdirectory(src/person_handling)