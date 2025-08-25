cmake_minimum_required(VERSION 3.31)
project(queue C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# FetchContent_MakeAvailable(googletest)

file(GLOB PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
)
add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "src/")
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
-Wall -Wpedantic -Wextra
-g
-fsanitize=address -fsanitize=undefined)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -fsanitize=address -fsanitize=undefined)

target_link_libraries(${CMAKE_PROJECT_NAME}
# GTest::gtest_main
)

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})
