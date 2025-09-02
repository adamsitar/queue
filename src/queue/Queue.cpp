#include <FixedBlock.h>
#include <Queue.h>
#include <RingBuffer.h>
#include <expected>
#include <types.h>

Result<void>
Queue::enqueue(unsigned char value)
{
  auto byte = static_cast<std::byte>(value);
  auto create_new_and_push =
    [byte](Element<RingBuffer>* element) -> Result<void> {
    element->element.add(byte);
    return {};
  };

  // if nothing in list, create and push
  if (list.head == nullptr) {
    list.push_back().and_then(create_new_and_push);
    return {};
  }

  // if last ring buffer is full, create new node and push
  if (list.tail->element.is_full()) {
    list.push_back().and_then(create_new_and_push);
    return {};
  }

  // if latest ring buffer has space, write into it
  if (list.tail->element.get_free() > 0) {
    list.tail->element.add(byte);
    return {};
  }
  return std::unexpected{ Error{ "Fallthrough!" } };
}

Result<std::byte>
Queue::dequeue()
{
  if (head == nullptr) {
    return std::unexpected{ Error{ "Can't dequeue byte from empty queue!" } };
  }

  auto tmp = head->element.remove().or_else(
    [](Error&& err) -> Result<std::byte> { return std::unexpected{ err }; });

  if (head->element.get_free() == 0 && !head->element.is_full()) {
    head = static_cast<Element<RingBuffer>*>(get_ptr_from_offset(head->next));
    FixedBlock::get_instance().free(head);
  }
  return tmp;
};

void
Queue::print() {};
