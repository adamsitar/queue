#pragma once
#include <List.h>
#include <RingBuffer.h>
#include <types.h>

struct Queue : private List<RingBuffer>
{
  delete_special_member_functions(Queue);
  Queue() = default;
  ~Queue() = default;
  using List<RingBuffer>::begin;
  using List<RingBuffer>::end;

  Result<void> enqueue(unsigned char value);
  Result<byte> dequeue();
  void print();

private:
  List<RingBuffer> list;
};
