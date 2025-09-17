find_package(GTest REQUIRED)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE
    GTest::gtest
    GTest::gtest_main
    queue_lib
    mbb
)

gtest_discover_tests(tests)
