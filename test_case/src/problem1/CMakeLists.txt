
cmake_minimum_required(VERSION 3.14)
project(problem1 LANGUAGES CXX)

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
include_directories(include)
# Define the executable target.
add_executable(problem1_exec src/main.cpp src/first_problem.cpp)
# Define the library target.
add_library(problem1_library src/first_problem.cpp)

#############
## Install ##
#############

# Install the cpp executables.
install(
  TARGETS problem1_exec
  DESTINATION bin/${PROJECT_NAME}
)

# Install the cpp library.
install(
  TARGETS problem1_library
  DESTINATION lib/${PROJECT_NAME}
)

#############
## Testing ##
#############

# Define the executable target.
add_executable(tests_first_problem tests/tests_first_problem.cpp)
# Link the GTest libary against it.
target_link_libraries(tests_first_problem gtest gtest_main problem1_library)
# Include the GTest libaries.
include(GoogleTest)
# Register the GTest test cases compiled in the executable.
gtest_discover_tests(tests_first_problem)