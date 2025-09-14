#pragma once
#include <cstddef>
#include <expected>
#include <print>

#define delete_special_member_functions(class_name)                            \
  class_name(const class_name&) = delete;                                      \
  class_name(const class_name&&) = delete;                                     \
  class_name& operator=(const class_name&) = delete;                           \
  class_name& operator=(const class_name&&) = delete;

struct Error
{
  std::string description{ "Undefined" };
};

template<typename U>
using Result = std::expected<U, Error>;

const constexpr size_t MAX_ALIGN{ alignof(std::max_align_t) };

#define TRY(expr)                                                              \
  ({                                                                           \
    auto&& result = (expr);                                                    \
    if (!result) {                                                             \
      return std::unexpected(result.error());                                  \
    }                                                                          \
    *result;                                                                   \
  })
