#pragma once
#include <cstdint>
#include <print>

#define delete_special_member_functions(class_name)                            \
  class_name(const class_name &) = delete;                                     \
  class_name(const class_name &&) = delete;                                    \
  class_name &operator=(const class_name &) = delete;                          \
  class_name &operator=(const class_name &&) = delete;
