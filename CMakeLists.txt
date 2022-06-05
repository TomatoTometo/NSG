cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 17)

project(nsg)

include(CTest)

find_package(GTest REQUIRED)

add_subdirectory(nsg)
add_subdirectory(test)
