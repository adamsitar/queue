find_package(benchmark REQUIRED)

add_executable(benchmarks benchmarks.cpp)
target_link_libraries(benchmarks PRIVATE
    queue_lib
    benchmark::benchmark
)
