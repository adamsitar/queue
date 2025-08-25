#include <linked_list.h>

template <typename T> linked_list<T>::~linked_list() {
  auto current{tail};
  list_element<T> *tail{};
  auto next{tail->next};
  freelist_allocator::get_instance().free(current);
  while (next)
    current = next;
}
template <typename T> T *linked_list<T>::push_back() {
  tail->next =
      new (freelist_allocator::get_instance().allocate()) list_element<T>;
  tail = tail->next;
  return tail;
}
template <typename T> void linked_list<T>::pop() {
  freelist_allocator::get_instance().free(head);
  head = head->next;
}
