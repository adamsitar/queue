add_subdirectory(queue)
add_subdirectory(mbb)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE queue_lib mbb)

