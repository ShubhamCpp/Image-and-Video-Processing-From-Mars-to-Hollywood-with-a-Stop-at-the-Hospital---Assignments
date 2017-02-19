cmake_minimum_required(VERSION 2.8) 
project (Test)
find_package(OpenCV REQUIRED )
set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "Test" )

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( Test Source.cpp )

target_link_libraries( Test ${OpenCV_LIBS} )