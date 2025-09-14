#include <memory_resource>
#include <types.h>

namespace mbb {

template<std::size_t BUFFER_SIZE>
class MonotonicResource : public std::pmr::memory_resource
{
  std::pmr::memory_resource* upstream;
  void* current;
  std::array<std::byte, BUFFER_SIZE> buffer;

public:
  explicit MonotonicResource(
    std::pmr::memory_resource* upstream = std::pmr::get_default_resource())
    : upstream(upstream)
    , current(buffer.data())
  {
  }

  void rewind() { current = buffer.data(); }

protected:
  [[nodiscard]] void* do_allocate(std::size_t bytes,
                                  std::size_t alignment) override
  {
    // 1. Calculate the total space remaining in our internal buffer.
    std::size_t space_left =
      static_cast<const std::byte*>(buffer.data() + BUFFER_SIZE) -
      static_cast<const std::byte*>(current);

    // 2. We use a copy of the current pointer for std::align to modify.
    void* ptr_to_align = current;

    // 3. std::align will adjust 'ptr_to_align' to the next available address
    //    that satisfies 'alignment' and reduce 'space_left' accordingly.
    //    If it succeeds, it returns the aligned pointer. Otherwise, nullptr.
    void* aligned_ptr = std::align(alignment, bytes, ptr_to_align, space_left);

    if (aligned_ptr != nullptr) {
      // SUCCESS: There is enough space in our internal buffer.

      // 4. Update the current pointer for the next allocation. It is now
      //    at the end of the block we just allocated.
      current = static_cast<std::byte*>(aligned_ptr) + bytes;

      // 5. Return the aligned pointer to the user.
      return aligned_ptr;
    }

    // FAILURE: There wasn't enough space in our buffer.
    // 6. Delegate the request to our upstream resource.
    return upstream->allocate(bytes, alignment);
  }
  void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override
  {
    // 1. Check if the pointer 'p' is within the address range of our buffer.
    const void* buffer_start = buffer.data();
    const void* buffer_end = buffer.data() + BUFFER_SIZE;

    // Note: Using >= and < is crucial for correct pointer-in-range checks.
    if (p >= buffer_start && p < buffer_end) {
      // The memory came from our internal buffer. In a monotonic allocator,
      // individual deallocations are a no-op. The memory will be reclaimed
      // all at once by rewind() or destruction.
      return;
    }

    // 2. If the pointer is not from our buffer, it must have come from
    // upstream.
    //    Delegate the deallocation call.
    upstream->deallocate(p, bytes, alignment);
  }

  [[nodiscard]] bool do_is_equal(
    const std::pmr::memory_resource& other) const noexcept override
  {
    // A MonotonicResource is stateful; it owns its specific buffer. It cannot
    // be considered equal to any other resource, not even another
    // MonotonicResource with an identical buffer, because they are distinct
    // objects with distinct allocation states.
    // The only resource it can be equal to is itself.
    return this == &other;
  }
};
}
