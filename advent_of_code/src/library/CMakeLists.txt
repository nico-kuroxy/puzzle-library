
cmake_minimum_required(VERSION 3.14)
project(advent_library LANGUAGES CXX)

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
add_library(advent_library src/base_advent_day.cpp)

#############
## Install ##
#############

# Install the cpp library.
install(
  TARGETS advent_library
  DESTINATION lib/${PROJECT_NAME}
)

# Install the header.
install(
  DIRECTORY include/library
  DESTINATION include)

#############
## Testing ##
#############

###################
## Documentation ##
###################
