cmake_minimum_required(VERSION 3.31)
project(queue C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
)
add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC $(PROJECT_SOURCES))
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wpedantic -Wextra)

# target_link_libraries(${CMAKE_PROJECT_NAME})
