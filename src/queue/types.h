#pragma once
#include <cstddef>
#include <cstdint>
#include <expected>
#include <print>
#include <string>

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

using byte = std::byte;

extern byte global_buffer[2048];

inline void*
get_ptr_from_offset(uint16_t offset) noexcept
{
  return global_buffer + offset;
}

inline uint16_t
get_offset_from_ptr(byte* ptr) noexcept
{
  return ptr - global_buffer;
}

template<typename T>
concept Printable = requires(const T& value) {
  { value.print() } -> std::same_as<void>;
};

inline void
on_illegal_operation() noexcept
{
  std::println("Illegal operation!");
}
