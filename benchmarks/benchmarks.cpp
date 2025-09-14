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
BENCHMARK_MAIN();
