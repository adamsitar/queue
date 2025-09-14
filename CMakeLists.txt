cmake_minimum_required(VERSION 4.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(queue CXX)

enable_testing()
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

function(set_common_compile_options target)
  target_compile_options(${target} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall -Wpedantic -Wextra -fdiagnostics-color=always>
    $<$<CONFIG:Debug>:
    -g -O2
    -fno-omit-frame-pointer
    -fsanitize=address
    # -fsanitize=thread
    # -fno-sanitize-recover=all
    >
  )
endfunction()

function(set_common_link_options target)
  target_link_options(${target} PRIVATE
    $<$<CONFIG:Debug>:
    -g -O2
    -fno-omit-frame-pointer
    -fsanitize=address
    # -fsanitize=thread
    # -fno-sanitize-recover=all
    >
  )
endfunction()

function(set_common_compile_features target visibility)
  target_compile_features(${target} ${visibility} cxx_std_23)
endfunction()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)
