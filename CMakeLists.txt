cmake_minimum_required(VERSION 3.2)

project (MatrixDSP)

#set(CMAKE_SUPPRESS_REGENERATION TRUE) # For doing test coverage
SET(CMAKE_CXX_FLAGS "-std=c++14")

include(gtest.cmake)
# GTest needs threading support
find_package (Threads)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    )
file (GLOB SOURCE_HEADERS "src/*.h")
 
AUX_SOURCE_DIRECTORY(test TEST_SOURCES)
add_executable (MatrixDspTests ${SOURCE_HEADERS} ${TEST_SOURCES})
target_link_libraries (MatrixDspTests gtest ${CMAKE_THREAD_LIBS_INIT})
add_definitions(-D_USE_MATH_DEFINES)
