#include <gtest/gtest.h>
#include <type_traits>

#define private public

#include "FixedBlock.h"

std::byte global_buffer[FixedBlock::POOL_SIZE];

TEST(FixedBlockTest, InitializesSingleton)
{
  auto& allocator = FixedBlock::get_instance();

  // Pool pointers are set and head is not null (all blocks free initially
  EXPECT_NE(allocator.pool_start, nullptr);
  EXPECT_NE(allocator.pool_end, nullptr);
  EXPECT_NE(allocator.head, nullptr);

  // Check pool size invariant
  EXPECT_EQ(reinterpret_cast<uintptr_t>(allocator.pool_end) -
              reinterpret_cast<uintptr_t>(allocator.pool_start),
            FixedBlock::POOL_SIZE);

  EXPECT_EQ(allocator.get_info().free, FixedBlock::BLOCK_COUNT)
    << "Initalized block count is not equal to supposed block count";
}

TEST(FixedBlockTest, AllocatesSingleBlock)
{
  auto& allocator = FixedBlock::get_instance();
  auto* block = allocator.allocate();
  ASSERT_NE(block, nullptr);

  // Check within pool bounds
  EXPECT_GE(block, allocator.pool_start);
  EXPECT_LT(block, allocator.pool_end);

  block->data[0] = (byte)21;

  allocator.reset();
  EXPECT_EQ(allocator.get_info().free, FixedBlock::BLOCK_COUNT)
    << "Initalized block count is not equal to supposed block count";
}

TEST(FixedBlockTest, FreesAndReallocates)
{
  auto& allocator = FixedBlock::get_instance();
  auto* block1 = allocator.allocate();

  ASSERT_NE(block1, nullptr);

  allocator.free(block1);

  auto* block2 = allocator.allocate();
  EXPECT_EQ(block1, block2);

  block2->data.fill(static_cast<byte>(20));

  EXPECT_EQ(block2->data[0], static_cast<byte>(20));

  allocator.reset();
  EXPECT_EQ(allocator.get_info().free, FixedBlock::BLOCK_COUNT)
    << "Initalized block count is not equal to supposed block count";
}

TEST(FixedBlockTest, ExhaustsPool)
{
  auto& allocator = FixedBlock::get_instance();
  std::vector<FixedBlock::Block*> blocks;
  blocks.reserve(FixedBlock::BLOCK_COUNT);

  for (size_t i = 0; i < FixedBlock::BLOCK_COUNT; ++i) {
    // std::println("i[{}] ", i);
    auto* block = allocator.allocate();
    ASSERT_NE(block, nullptr);
    blocks.push_back(block);
  }

  // Cleanup
  for (auto* block : blocks) {
    allocator.free(block);
  }

  // Repeat for another round to check re-usability
  auto* extra = allocator.allocate();
  EXPECT_NE(extra, nullptr);
  allocator.free(extra);

  EXPECT_EQ(allocator.get_info().free, FixedBlock::BLOCK_COUNT)
    << "Initalized block count is not equal to supposed block count";
}

#undef private
