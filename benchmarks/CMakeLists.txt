add_executable(benchmarks benchmarks.cpp)
target_link_libraries(benchmarks PRIVATE
    queue_lib
    benchmark::benchmark
)
set_common_compile_features(benchmarks PRIVATE)
set_common_compile_options(benchmarks)
set_common_link_options(benchmarks)
