macro(create_test TEST_FILE)

  message(STATUS "[DEV] Generating test for file ${TEST_FILE}")
  
  get_filename_component(TEST_EXE ${TEST_FILE} NAME_WLE)
  
  # add the executable
  add_executable(${TEST_EXE} ${TEST_FILE})
  
  target_link_libraries(${TEST_EXE} PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    GTest::gmock
  )

  target_include_directories(${TEST_EXE} PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  add_test(NAME ${TEST_EXE} COMMAND ${TEST_EXE})

endmacro()

#[[

References:
+ https://google.github.io/googletest/
  + https://google.github.io/googletest/primer.html
  + https://google.github.io/googletest/advanced.html
  + https://google.github.io/googletest/gmock_for_dummies.html
  + https://google.github.io/googletest/reference/testing.html
  + https://google.github.io/googletest/reference/mocking.html


You can run --help on the gtest executable to see a list of options 
you can pass to the gtest

Here are some of my favorites:

  --gtest_filter=POSITIVE_PATTERNS[-NEGATIVE_PATTERNS]
      Run only the tests whose name matches one of the positive patterns but
      none of the negative patterns. '?' matches any single character; '*'
      matches any substring; ':' separates two patterns.
  --gtest_repeat=[COUNT]
      Run the tests repeatedly; use a negative count to repeat forever.
  --gtest_shuffle
      Randomize tests' orders on every iteration. 
      There is another option to provide a random number seed to use for shuffling
  --gtest_break_on_failure
      Turn assertion failures into debugger break-points.

  Example ./gtest_TEST_P.exe --gtest_shuffle --gtest_repeat=5 --gtest_filter=*1

Example of custom matcher

  EXPECT_THAT(2, IsEven());


Example of mock expectation calls

Actions
 + Return*
 + Side effects
 + Invoke another function
 + DoAll
 + Developer can define functions

Cardinalities
 + Times (cardinality)
   + AnyNumber
   + AtLeast
   + AtMost
   + Between
   + Exactly
Expectation Order
 + After
 + InSequense


]]

create_test(gtest_TEST.cpp)
create_test(gtest_TEST_F.cpp)
create_test(gtest_TEST_P.cpp)
create_test(gtest_GMOCK.cpp)