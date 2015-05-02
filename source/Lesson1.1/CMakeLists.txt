cmake_minimum_required (VERSION 2.8)
project (lesson1.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

# set(SOURCE_FILES main.cpp)

#include the subdirectory containing our libs
# add_subdirectory (src)

include_directories(../Library ../../../gl3w/include)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../../../glfw/src
	${CMAKE_CURRENT_SOURCE_DIR}/../../../gl3w
)

add_executable (lesson1.1 Program.cpp)

target_link_libraries (lesson1.1 gl3w glfw GL)
