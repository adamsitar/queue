# Test executable
add_executable(tests)
target_sources(tests PRIVATE test.cpp)
target_link_libraries(tests PRIVATE
    queue_lib
    GTest::gtest_main
)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src/queue)
set_common_compile_features(tests PRIVATE)
set_common_compile_options(tests)
set_common_link_options(tests)

include(GoogleTest)
gtest_discover_tests(tests)
