
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
include_directories(include ${CMAKE_SOURCE_DIR}/install/include)
# Define the executable target.
add_executable(mull_over src/main.cpp src/mull_over.cpp)
# Point to the installed library path
link_directories(${CMAKE_SOURCE_DIR}/install/lib/advent_library)
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

###################
## Documentation ##
###################
