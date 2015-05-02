cmake_minimum_required (VERSION 2.8)
project (lesson1.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

# set(SOURCE_FILES main.cpp)

#include the subdirectory containing our libs
# add_subdirectory (src)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../Library 
	${CMAKE_CURRENT_SOURCE_DIR}/../../external/gl3w/include
	# ${CMAKE_CURRENT_SOURCE_DIR}/../../external/glm
	# ${CMAKE_CURRENT_SOURCE_DIR}/../../external/glfw/source/include
	)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../../external/gl3w
	# ${CMAKE_CURRENT_SOURCE_DIR}/../../external/glm
	# ${CMAKE_CURRENT_SOURCE_DIR}/../../external/glfw/source/src
)

add_executable (lesson1.1 Program.cpp)

target_link_libraries (lesson1.1 gl3w glfw GL)
