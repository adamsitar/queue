file(GLOB QUEUE_SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB QUEUE_PRIVATE_HEADERS CONFIGURE_DEPENDS "*.h")

add_library(queue_lib STATIC)

target_sources(queue_lib
  PRIVATE
    ${QUEUE_SOURCES}
  PRIVATE
    FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${QUEUE_PRIVATE_HEADERS}
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
    FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/Queue.h"
)

# target_include_directories(queue_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
# target_include_directories(queue_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(queue_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
