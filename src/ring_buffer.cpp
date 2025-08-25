#include <expected>
#include <freelist_allocator.h>
#include <print>
#include <ring_buffer.h>

extern std::byte global_buffer[2048];
inline std::byte *get_ptr_from_offset(uint16_t offset) noexcept {
  return global_buffer + offset;
}

void ring_buffer::push(std::byte value) {
  storage[tail] = value;
  tail = (tail + 1) % STORAGE_SIZE;
};
std::byte ring_buffer::pop() {
  std::byte value = storage[head];
  head = (head + 1) % STORAGE_SIZE;
  return value;
};

uint8_t ring_buffer::get_free_slots() { return head - tail; }

void ring_buffer::print() {
  if (head == tail) {
    std::println("Ring buffer empty");
    return;
  }
  std::println("Storage tail: {}, Head: {}", tail, head);
  for (int i{head}; i < tail; i++) {
    std::print("{} ", static_cast<uint8_t>(storage[i]));
  }
};

template <typename T> void linked_list<T>::print() {
  bool finished{false};
  int elem_count{};
  list_element<ring_buffer> *current{tail};

  while (!finished) {
    std::println("Element[{}]:", elem_count);
    current->element.print();
    if (current->next) {
      elem_count++;
      current = reinterpret_cast<list_element<ring_buffer> *>(
          get_ptr_from_offset(current->next));
    } else {
      finished = true;
    }

    printf("\n");
  }
}
