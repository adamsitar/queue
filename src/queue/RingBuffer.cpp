#include <FixedBlock.h>
#include <RingBuffer.h>

#include <expected>
#include <print>

Result<void>
RingBuffer::add(std::byte value)
{
  tail = (tail + 1) % STORAGE_SIZE;
  if ((tail == head) && full) {
    return std::unexpected{ Error{ "Ring buffer full!" } };
  }
  storage[tail] = value;
  return {};
};

Result<std::byte>
RingBuffer::remove()
{
  // if buffer is empty
  if ((head == tail) && !full) {
    return std::unexpected{ Error{ "Can't remove from empty ring buffer!" } };
  }

  std::byte temp = storage[head];
  head = (head + 1) % STORAGE_SIZE;
  return temp;
};

uint8_t
RingBuffer::get_free() const
{
  return abs(tail - head);
}

bool
RingBuffer::is_full() const
{
  return full;
};

void
RingBuffer::print()
{
  std::println("Tail: {}, Head: {}", tail, head);
  if ((tail == head) && !full) {
    std::println("RingBuffer empty");
    return;
  }

  for (int i{ head }; i < tail; i++) {
    std::print("{} ", static_cast<uint8_t>(storage[i]));
  }
};
