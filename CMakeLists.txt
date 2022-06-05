

cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 17)




# set the project name
project(myPie)

include(CTest)

find_package(GTest REQUIRED)

message(STATUS "GTest_INCLUDE_DIRS is ${GTEST_INCLUDE_DIRS}" )
message(STATUS "GTest_LIBRARIES is ${GTEST_BOTH_LIBRARIES}" )

# add the executable
add_executable(myPie main.cpp)

target_link_libraries(myPie PUBLIC
  # gmock
  # foo
  ${GTEST_BOTH_LIBRARIES}
)



target_include_directories(myPie
PUBLIC
  ${GTest_INCLUDE_DIRS}
)

# install(FILES ./example.py DESTINATION ${CMAKE_BINARY_DIR})


enable_testing()


add_subdirectory(test)
