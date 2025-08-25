#include "freelist_allocator.h"
#include <queue.h>
std::byte global_buffer[2048];

int main(void) {
  freelist_allocator::get_instance();

  queue q1;
  q1.print();
  q1.enqueue_byte(1);
  q1.enqueue_byte(58);
  q1.enqueue_byte(238);
  q1.print();
  std::println("deque print: {}", q1.dequeue_byte());
  std::println("deque print: {}", q1.dequeue_byte());
  std::println("deque print: {}", q1.dequeue_byte());
  q1.print();
}
