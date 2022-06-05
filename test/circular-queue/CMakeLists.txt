
# add the executable
add_executable(test-circular-queue gtest_circular_queue.cpp)

target_link_libraries(test-circular-queue PUBLIC
  ${GTEST_BOTH_LIBRARIES}
)

message(STATUS "GTest_INCLUDE_DIRS is ${GTest_INCLUDE_DIRS}" )
message(STATUS "GTEST_BOTH_LIBRARIES is ${GTEST_BOTH_LIBRARIES}" )

target_include_directories(test-circular-queue PUBLIC
  ${GTest_INCLUDE_DIRS}
)


add_test(NAME test-circular-queue COMMAND test-circular-queue)
