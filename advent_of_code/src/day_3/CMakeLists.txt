
cmake_minimum_required(VERSION 3.14)
project(day_3 LANGUAGES CXX)

#########################
## Compilation options ##
#########################

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 17)

# Handle debugging flags.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

###########################
## Find system libraries ##
###########################

###########
## Build ##
###########

# Let the compiler search for headers in the include folder.
include_directories(include ${CMAKE_SOURCE_DIR}/src/library/include)
# Define the executable target.
add_executable(mull_over src/main.cpp src/mull_over.cpp)
# Link the library against it.
target_link_libraries(mull_over advent_library)

#############
## Install ##
#############

# Install the cpp executables.
install(
  TARGETS mull_over
  DESTINATION bin/${PROJECT_NAME}
)

# Install the data files.
install(
  DIRECTORY data/
  DESTINATION share/${PROJECT_NAME}/data
)

#############
## Testing ##
#############

# Define the executable target.
add_executable(tests_mull tests/test_mull_over.cpp src/mull_over.cpp)
# Link the GTest libary against it.
target_link_libraries(tests_mull gtest gtest_main advent_library)
# Include the GTest libaries.
include(GoogleTest)
# Register the GTest test cases compiled in the executable.
gtest_discover_tests(tests_mull)

###################
## Documentation ##
###################
