
cmake_minimum_required(VERSION 3.14)
project(day_2 LANGUAGES CXX)

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
add_executable(red_reports src/main.cpp src/red_reports.cpp)

#############
## Install ##
#############

# Install the cpp executables.
install(
  TARGETS red_reports
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

###################
## Documentation ##
###################
