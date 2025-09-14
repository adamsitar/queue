add_subdirectory(queue)
add_subdirectory(mbb)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE queue_lib mbb)
set_common_compile_options(main)
set_common_link_options(main)
