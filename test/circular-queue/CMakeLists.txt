
# add the executable
add_executable(test-circular-queue gtest_circular_queue.cpp)

target_link_libraries(test-circular-queue PUBLIC
  ${GTEST_BOTH_LIBRARIES}
)

target_include_directories(test-circular-queue PUBLIC
  ${PROJECT_SOURCE_DIR}
)
add_test(NAME test-circular-queue COMMAND test-circular-queue)
