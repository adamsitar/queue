#include <MonotonicResource.h>

using namespace mbb;

template<typename std::size_t BUFFER_SIZE>
[[nodiscard]] void*
MonotonicResource<BUFFER_SIZE>::do_allocate(std::size_t bytes,
                                            std::size_t alignment)
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
