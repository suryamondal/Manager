
cmake_minimum_required(VERSION 3.9)

# set the project name
project(Manager)


# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1y -m64")

#including root
find_package(ROOT CONFIG REQUIRED)
# find_package(ROOT COMPONENTS Minuit)
# Setup Root include directories and compile definitions
include("${ROOT_USE_FILE}")

# Setup include directory for this project
include_directories(${PROJECT_SOURCE_DIR}/include)

add_compile_options(-Wall -Wextra -pedantic)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB headers1 ${PROJECT_SOURCE_DIR}/include/*.hh)

separate_arguments(ROOT_EXE_LINKER_FLAGS)
add_executable(Manager src/test.cpp ${sources} ${headers} ${headers1})

target_include_directories(Manager PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Manager PUBLIC ${ROOT_LIBRARIES} ${ROOT_EXE_LINKER_FLAGS})

# # specify the C++ standard
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS Manager DESTINATION bin)
