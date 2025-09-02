#pragma once
#include <gtest/gtest_prod.h>
#include <types.h>

struct FixedBlock
{
  const static constexpr size_t BLOCK_SIZE{ 32 };
  const static constexpr size_t POOL_SIZE{ 2048 };
  const static constexpr size_t BLOCK_COUNT{ POOL_SIZE / BLOCK_SIZE };

  union alignas(BLOCK_SIZE) Block
  {
    Block* next_free;
    std::array<byte, BLOCK_SIZE> data;
  };

  static FixedBlock& get_instance();
  Block* allocate();
  void free(void* ptr);
  void reset();

  struct Info
  {
    short free;
  };
  Info get_info();
  static void on_out_of_memory();

  delete_special_member_functions(FixedBlock);
  ~FixedBlock() = default;

private:
  FixedBlock();

  Block* head{ nullptr };
  void* pool_start{ nullptr };
  void* pool_end{ nullptr };
};

// using Pool = std::array<byte, FixedBlock::POOL_SIZE>;
// Pool&
// get_pool()
// {
//   static Pool pool;
//   return pool;
// };
