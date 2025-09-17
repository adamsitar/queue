cmake_minimum_required(VERSION 4.1.0)

function(set_common_compile_options target)
  target_compile_options(${target} PRIVATE

    # --- Debug flags --
    $<$<CONFIG:Debug>:
      # -g -O0
      -fno-omit-frame-pointer
      -fsanitize=address
      # -fsanitize=thread
      # -fno-sanitize-recover=all
    >
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:
      -coverage
      -fprofile-instr-generate
      -fcoverage-mapping
    >
  )
endfunction()

function(set_common_link_options target)
  target_link_options(${target} PRIVATE
    $<$<CONFIG:Debug>:
    # -g -O0
    -fno-omit-frame-pointer
    -fsanitize=address
    # -fsanitize=thread
    # -fno-sanitize-recover=all
    >
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>>:
    -fprofile-instr-generate
    -fcoverage-mapping>
  )
endfunction()

function(set_common_compile_features target visibility)
  target_compile_features(${target} ${visibility} cxx_std_23)
endfunction()

function(setup_target target visibility)
  set_common_compile_features(${target} ${visibility})
  set_common_compile_options(${target} ${visibility})
  set_common_link_options(${target} ${visibility})
endfunction()
