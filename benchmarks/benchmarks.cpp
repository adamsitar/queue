#include <FixedBlock.h>
#include <benchmark/benchmark.h>

std::byte global_buffer[FixedBlock::POOL_SIZE];

static void
BM_Allocate(benchmark::State& state)
{
  for (auto _ : state) {
    FixedBlock::get_instance().allocate();
  }
}
BENCHMARK(BM_Allocate);

class Spinlock
{
public:
  void lock()
  {
    while (flag_.exchange(1, std::memory_order_acquire)) {
    }
  }
  void unlock() { flag_.store(0, std::memory_order_release); }

private:
  std::atomic<unsigned int> flag_;
};

std::mutex m;
size_t count = 0;
void
BM_lock(benchmark::State& state)
{
  if (state.thread_index() == 0)
    count = 0;
  for (auto _ : state) {
    std::lock_guard l(m);
    ++count;
  }
}
BENCHMARK(BM_lock)->Threads(2)->UseRealTime();

BENCHMARK_MAIN();
