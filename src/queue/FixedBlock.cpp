#include <FixedBlock.h>
#include <csignal>
#include <cstring>
#include <types.h>

#include <print>

FixedBlock::FixedBlock()
  : pool_start(global_buffer)
  , pool_end(global_buffer + FixedBlock::POOL_SIZE)
{
  auto* pool = reinterpret_cast<Block*>(global_buffer);

  for (size_t i = 0; i < BLOCK_COUNT - 1; ++i) {
    pool[i].next_free = &pool[i + 1];
  }

  pool[BLOCK_COUNT - 1].next_free = nullptr;
  head = &pool[0];
}

FixedBlock::Block*
FixedBlock::allocate()
{
  if (head == nullptr) {
    return nullptr;
    // FreelistAllocator::on_out_of_memory();
  }

  Block* chunk_to_allocate = head;
  head = head->next_free;

  return chunk_to_allocate;
}

void
FixedBlock::free(void* ptr)
{
  if (ptr == nullptr) {
    return; // Nothing to free
  }
  if (ptr < pool_start || ptr >= pool_end) {
    return;
  }

  auto* freed_chunk = std::construct_at(static_cast<Block*>(ptr));
  freed_chunk->next_free = head;

  head = freed_chunk;
}

void
FixedBlock::on_out_of_memory()
{
  std::println("Out of memory!");
};

FixedBlock&
FixedBlock::get_instance()
{
  static FixedBlock instance;
  return instance;
};

void
FixedBlock::reset()
{
  std::memset(global_buffer, 0, POOL_SIZE);
  std::byte global_buffer[FixedBlock::POOL_SIZE];
  new (this) FixedBlock();
}

FixedBlock::Info
FixedBlock::get_info()
{
  // Initalize to 1 to account for the first block that's already set
  short count{ 1 };
  auto current{ this->head };
  while (current->next_free != nullptr) {
    count++;
    current = current->next_free;
  };

  return { FixedBlock::Info{ count } };
}
