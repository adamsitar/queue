file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB PRIVATE_HEADERS CONFIGURE_DEPENDS "*.h")

add_library(mbb STATIC)

target_sources(mbb
  PRIVATE
    ${SOURCES}
  PRIVATE
    FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${PRIVATE_HEADERS}
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
    FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/MonotonicResource.h"
)

target_include_directories(mbb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(mbb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(mbb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
