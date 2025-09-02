#include "FixedBlock.h"
#include "Queue.h"

std::byte global_buffer[FixedBlock::POOL_SIZE];

int
main()
{
  Queue queue1{};
  queue1.print();

  queue1.enqueue(1);
  queue1.enqueue(58);
  queue1.enqueue(238);

  queue1.print();
}
