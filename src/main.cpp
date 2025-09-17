#include "queue/Queue.h"
#include <FixedBlock.h>
#include <MonotonicResource.h>

std::byte global_buffer[FixedBlock::POOL_SIZE];

int
main()
{
  Queue queue1{};
  queue1.print();

  // mbb::MonotonicResource<1024> buf;

  queue1.enqueue(1);
  queue1.enqueue(58);
  queue1.enqueue(238);

  queue1.print();
}
