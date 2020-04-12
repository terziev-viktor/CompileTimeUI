cmake_minimum_required(VERSION 3.0.0)
project(CompileTime VERSION 0.1.0)

include(CTest)
enable_testing()

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++2a -fconcepts -O3")
set(Commands
      ${CMAKE_CURRENT_LIST_DIR}/Commands/Calc.cpp
      ${CMAKE_CURRENT_LIST_DIR}/Commands/Print.cpp
      ${CMAKE_CURRENT_LIST_DIR}/Commands/Say.cpp)
      
add_executable(CompileTime main.cpp ${Commands})

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
