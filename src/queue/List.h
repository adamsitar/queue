#pragma once
#include <FixedBlock.h>
#include <cstdint>
#include <types.h>

template<typename T>
struct Element
{
  delete_special_member_functions(Element);
  Element() = default;
  ~Element() = default;

  T element{};
  uint8_t next{ 0 }; // index of chunk
  static constexpr uint8_t HEADER_SIZE{ sizeof(next) };
};

template<typename T>
struct List
{
  delete_special_member_functions(List);
  List() = default;
  ~List();

  Element<T>* tail{ nullptr };
  Element<T>* head{ nullptr };

  struct iterator
  {
    explicit iterator(Element<T>* ptr)
      : ptr(ptr)
    {
    }
    T& operator*() const { return *ptr; }
    T* operator->() { return ptr; }
    iterator& operator++()
    {
      ptr = get_ptr_from_offset(ptr->next);
      return *this;
    }
    iterator operator++(int)
    {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator!=(const iterator& left, const iterator& right)
    {
      return left.ptr != right.ptr;
    };
    friend bool operator==(const iterator& left, const iterator& right)
    {
      return left.ptr == right.ptr;
    };

  private:
    Element<T>* ptr;
  };

  iterator begin() { return iterator{ head }; };
  iterator end() { return iterator{ nullptr }; };
  void print() const
    requires Printable<T>;

  std::expected<Element<T>*, Error> push_back()
    requires std::is_default_constructible_v<T>; // increment tail
  std::expected<Element<T>, Error> pop();        // increment head

  static_assert(sizeof(Element<T>) <= FixedBlock::BLOCK_SIZE,
                "list_element<T> is too large for the allocator's chunk size");
};

template<typename T>
List<T>::~List()
{
  Element<T>* current{ head };
  while (current != nullptr) {
    auto next{ current->next };
    FixedBlock::get_instance().free(current);
    current = static_cast<Element<T>*>(get_ptr_from_offset(next));
  }
}

template<typename T>
std::expected<Element<T>*, Error>
List<T>::push_back()
  requires std::is_default_constructible_v<T>
{
  // if list is empty
  if ((tail == head) && head == nullptr) {
    tail = std::construct_at(
      reinterpret_cast<Element<T>*>(FixedBlock::get_instance().allocate()));
    return head = tail;
  }

  auto new_elem{ std::construct_at(FixedBlock::get_instance().allocate()) };
  tail->next = get_offset_from_ptr(reinterpret_cast<byte*>(new_elem));
  return tail = reinterpret_cast<Element<T>*>(new_elem);
}

template<typename T>
std::expected<Element<T>, Error>
List<T>::pop()
{
  if ((tail == head) && head == nullptr) {
    on_illegal_operation();
    return Error{ "Can't pop from an empty list!" };
  }
  Element<T> tmp = *head;
  FixedBlock::get_instance().free(head);
  head = tmp->next;
  return tmp;
}

template<typename T>
void
List<T>::print() const
  requires Printable<T>
{
  Element<T>* current{ tail };

  std::println("Printing list:");
  if (head == nullptr) {
    std::println("List empty");
    return;
  }
  for (const auto& value : *this) {
    value.print();
  }
}
