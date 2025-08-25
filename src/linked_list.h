#pragma once
#include <cstdint>
#include <freelist_allocator.h>

template <typename T> struct list_element {
  // delete_special_member_functions(list_element);
  // offset from beginning of buffer, in bytes
  uint16_t next{0};
  T element{};
  static constexpr uint8_t HEADER_SIZE{sizeof(next)};
};

template <typename T> struct linked_list {
  // creates the first element in the list on construction of itself
  list_element<T> *head{new (freelist_allocator::get_instance().allocate())
                            list_element<T>};
  list_element<T> *tail{head};

  // increment tail
  T *push_back();
  // decrement head
  void pop();
  void print();
  linked_list();
  ~linked_list();
};
