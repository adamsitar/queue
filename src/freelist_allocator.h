#pragma once
#include <cstddef>
#include <optional>
#define BUFFER_SIZE 2048
#define BLOCK_SIZE 32

extern std::byte global_buffer[BUFFER_SIZE];

class freelist_allocator {
public:
  static constexpr size_t CHUNK_SIZE{32};
  static constexpr size_t POOL_SIZE{2048};
  static constexpr size_t NUM_CHUNKS{POOL_SIZE / CHUNK_SIZE};

  union chunk {
    chunk *next_free;
    std::byte data[CHUNK_SIZE];
  };

  static freelist_allocator &get_instance();
  std::optional<chunk *> allocate();
  void free(void *ptr);
  void on_out_of_memory();

  freelist_allocator(const freelist_allocator &) = delete;
  freelist_allocator &operator=(const freelist_allocator &) = delete;
  freelist_allocator(freelist_allocator &&) = delete;
  freelist_allocator operator=(freelist_allocator &&) = delete;

private:
  freelist_allocator();

  chunk *head;
  void *pool_start = nullptr;
  void *pool_end = nullptr;
};
