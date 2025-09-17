/**
 * @file Greeter.h
 * @brief Declares the public API for the Greeter library.
 *
 * This is the primary file that you should #include if
 * you want to use the library.
 */
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

  /**
   * @brief Provides a friendly greeting.
   *
   * This function generates a greeting string that can be
   * displayed to the user. It's the core feature of the
   * Greeter library.
   *
   * @return A std::string containing the greeting.
   *
   * @code
   * #include <iostream>
   * #include <greeter/Greeter.h>
   * int main() {
   *   std::cout << get_greeting(); // Prints the greeting
   * }
   * @endcode
   */
  Result<void> enqueue(unsigned char value);
  Result<byte> dequeue();
  void print();

private:
  List<RingBuffer> list;
};
