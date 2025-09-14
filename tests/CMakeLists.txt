add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE
    queue_lib
    GTest::gtest_main
)
set_common_compile_features(tests PRIVATE)
set_common_compile_options(tests)
set_common_link_options(tests)

gtest_discover_tests(tests)
