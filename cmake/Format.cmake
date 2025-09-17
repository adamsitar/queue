
find_program(CLANG_FORMAT_EXE clang-format)
set(FORMAT_TARGETS queue_lib mbb)
set(ALL_SOURCES)

# get_target_property(
#   private_headers queue_lib HEADER_SET_private_headers
# )
# message(STATUS "private_headers: ${private_headers}")
#
# get_target_property(
#   public_headers queue_lib HEADER_SET_public_headers
# )
# message(STATUS "public_headers: ${public_headers}")

foreach(target IN LISTS FORMAT_TARGETS)
  get_target_property(target_sources ${target} SOURCES)
  get_target_property(target_sources ${target} HEADER_SET_public_headers)
  get_target_property(target_sources ${target} HEADER_SET_private_headers)
  get_target_property(target_source_dir ${target} SOURCE_DIR)

  # Combine sources and headers into one list to process
  set(current_target_files ${target_sources} ${target_headers})

  # Convert relative paths to absolute paths for this target
  foreach(file IN LISTS current_target_files)
    if(IS_ABSOLUTE ${file} AND EXISTS ${file})
      list(APPEND ALL_SOURCES ${file})
    elseif(EXISTS ${target_source_dir}/${file})
      list(APPEND ALL_SOURCES ${target_source_dir}/${file})
    endif()
  endforeach()
endforeach()

if(CLANG_FORMAT_EXE)
  add_custom_target(format
    COMMENT "Formatting files with clang-format..."
    COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCES}
  )
  message(STATUS "Added 'format' target")
else()
  message(WARNING
    "clang-format not found - format target unavailable")
endif()
