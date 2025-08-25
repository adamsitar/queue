#include <queue.h>

void queue::enqueue_byte(unsigned char value) { list.push_back(); };
unsigned char queue::dequeue_byte() {};

void queue::print() { list.print(); };
void queue::on_illegal_operation() { std::println("Illegal operation!"); };
