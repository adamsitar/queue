#pragma once
#include <linked_list.h>
#include <ring_buffer.h>
#include <types.h>

struct queue {
  delete_special_member_functions(queue);
  linked_list<ring_buffer> list;

  void enqueue_byte(unsigned char value);
  unsigned char dequeue_byte();
  void print();

private:
  void on_illegal_operation();
};
