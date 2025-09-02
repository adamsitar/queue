#pragma once
#include <FixedBlock.h>
#include <List.h>
#include <types.h>

struct RingBuffer
{
private:
  uint8_t head{ 0 }; // increment to remove
  uint8_t tail{ 0 }; // increment to insert
  bool full{ false };
  static constexpr uint8_t HEADER_SIZE{ sizeof(head) + sizeof(tail) +
                                        sizeof(full) };
  static constexpr uint8_t STORAGE_SIZE{ FixedBlock::BLOCK_SIZE - HEADER_SIZE -
                                         Element<int>::HEADER_SIZE };
  std::array<byte, STORAGE_SIZE> storage{};

public:
  Result<void> add(byte value); // incremens tail
  Result<byte> remove();        // increments head
  void print();
  [[nodiscard]] bool is_full() const;
  [[nodiscard]] uint8_t get_free() const;
};
