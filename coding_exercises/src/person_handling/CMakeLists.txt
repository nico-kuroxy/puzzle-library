
cmake_minimum_required(VERSION 3.14)
project(person_handling LANGUAGES CXX)

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
# Define the library target.
add_library(person_handling src/person_handler.cpp)

#############
## Install ##
#############

# Install the cpp library.
install(
  TARGETS person_handling
  DESTINATION lib/${PROJECT_NAME}
)

#############
## Testing ##
#############

# Define the executable target.
add_executable(tests_person_handler tests/tests_person_handler.cpp)
# Link the GTest libary against it.
target_link_libraries(tests_person_handler gtest gtest_main person_handling)
# Include the GTest libaries.
include(GoogleTest)
# Register the GTest test cases compiled in the executable.
gtest_discover_tests(tests_person_handler)