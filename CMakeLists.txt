cmake_minimum_required(VERSION 2.8)

project (MatrixDSP)

#set(CMAKE_SUPPRESS_REGENERATION TRUE) # For doing test coverage
SET(CMAKE_CXX_FLAGS "-std=c++14")

file (GLOB SOURCE_HEADERS "src/*.h")

set( GOOGLETEST_DIR ../googletest-read-only )
INCLUDE_DIRECTORIES(src ${GOOGLETEST_DIR}/include)
add_subdirectory (${GOOGLETEST_DIR} gtest)

AUX_SOURCE_DIRECTORY(test TEST_SOURCES)
add_executable (MatrixDspTests ${SOURCE_HEADERS} ${TEST_SOURCES})
target_link_libraries (MatrixDspTests gtest)
add_definitions(-D_USE_MATH_DEFINES)
