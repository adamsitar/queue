#include "freelist_allocator.h"
#include <print>

freelist_allocator::freelist_allocator() {
  pool_start = global_buffer;
  pool_end = global_buffer + BUFFER_SIZE;
  chunk *pool = reinterpret_cast<chunk *>(global_buffer);

  for (size_t i = 0; i < NUM_CHUNKS - 1; ++i) {
    pool[i].next_free = &pool[i + 1];
  }

  pool[NUM_CHUNKS - 1].next_free = nullptr;
  head = &pool[0];

  std::println("freelist allocator is initalized");
}

std::optional<freelist_allocator::chunk *> freelist_allocator::allocate() {
  if (head == nullptr) {

    return {};
  }

  chunk *chunk_to_allocate = head;
  head = head->next_free;

  return chunk_to_allocate;
}

void freelist_allocator::on_out_of_memory() { std::println("Out of memory!"); };

void freelist_allocator::free(void *ptr) {
  if (ptr == nullptr) {
    return; // Nothing to free
  }
  if (ptr < pool_start || ptr >= pool_end) {
    return;
  }

  chunk *freed_chunk = static_cast<chunk *>(ptr);
  freed_chunk->next_free = head;

  head = freed_chunk;
}

freelist_allocator &freelist_allocator::get_instance() {
  static freelist_allocator instance;
  return instance;
};
