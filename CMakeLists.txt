cmake_minimum_required(VERSION 3.0.0)
project(CompileTime VERSION 0.1.0)

include(CTest)
enable_testing()

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++2a -fconcepts -O3")

add_executable(CompileTime main.cpp)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
