cmake_minimum_required(VERSION 3.0)

project(compression)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(
	src
	${OpenCV_INCLUDE_DIRS})

set( SOURCES  
	src/source.cpp
)

add_executable( compression ${SOURCES} )

target_link_libraries(compression ${OpenCV_LIBS})