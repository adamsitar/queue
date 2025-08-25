#pragma once
#include "freelist_allocator.h"
#include <cstdint>
#include <linked_list.h>
#include <types.h>

struct ring_buffer {
  uint8_t head{0}; // extract
  uint8_t tail{0}; // insert
  static constexpr uint8_t HEADER_SIZE{sizeof(head) + sizeof(tail)};
  static constexpr uint8_t STORAGE_SIZE{freelist_allocator::CHUNK_SIZE -
                                        HEADER_SIZE - sizeof(uint16_t)};
  std::byte storage[STORAGE_SIZE];

  // these two don't care about the fullness of the buffer
  void push(std::byte value);
  std::byte pop();
  void print();
  uint8_t get_free_slots();
};
