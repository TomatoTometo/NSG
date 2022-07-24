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



-----------------    gtest_TEST:

[==========] Running 3 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from sillyBinarySearch
[ RUN      ] sillyBinarySearch.FindsValueTowardsEndOfData
[       OK ] sillyBinarySearch.FindsValueTowardsEndOfData (0 ms)
[ RUN      ] sillyBinarySearch.FindsValueTowardsStartOfData
[       OK ] sillyBinarySearch.FindsValueTowardsStartOfData (0 ms)
[----------] 2 tests from sillyBinarySearch (0 ms total)

[----------] 1 test from itemsInArray
[ RUN      ] itemsInArray.areBiggerThanValue
gtest_TEST.cpp:64: Failure
Value of: data[i]
Expected: is < 5
Actual: 5 (of type unsigned int)
[MORE INFO] Test failed at i = 4

[  FAILED  ] itemsInArray.areBiggerThanValue (0 ms)
[----------] 1 test from itemsInArray (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 2 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] itemsInArray.areBiggerThanValue

-----------------    gtest_TEST_P:

[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from MySillyBinaryTestSuite/sillyBinarySearch
[ RUN      ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/0
[       OK ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/0 (0 ms)
[ RUN      ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/1
[       OK ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/1 (0 ms)
[ RUN      ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/2
[       OK ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/2 (0 ms)
[ RUN      ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/3
[       OK ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/3 (0 ms)
[ RUN      ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/4
[       OK ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/4 (0 ms)
[ RUN      ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/5
[       OK ] MySillyBinaryTestSuite/sillyBinarySearch.FindsValueInData/5 (0 ms)
[----------] 6 tests from MySillyBinaryTestSuite/sillyBinarySearch (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 6 tests.


-----------------    gtest_TEST_F:

[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from sillyBinarySearch
[    >>>   ] Here calling << SetUpTestSuite!
[ RUN      ] sillyBinarySearch.FindsValueTowardsEndOfData
[    >>    ] Here calling << SetUp!
[    >>    ] Here calling << TearDown!
[       OK ] sillyBinarySearch.FindsValueTowardsEndOfData (0 ms)
[ RUN      ] sillyBinarySearch.FindsValueTowardsStartOfData
[    >>    ] Here calling << SetUp!
[    >>    ] Here calling << TearDown!
[       OK ] sillyBinarySearch.FindsValueTowardsStartOfData (0 ms)
[    >>>   ] Here calling << TearDownTestSuite!
[----------] 2 tests from sillyBinarySearch (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.




]]

create_test(gtest_TEST.cpp)
create_test(gtest_TEST_F.cpp)
create_test(gtest_TEST_P.cpp)
create_test(gtest_GMOCK.cpp)