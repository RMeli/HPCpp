#include <umpire/ResourceManager.hpp>
#include <umpire/Umpire.hpp>
#include <umpire/strategy/PoolCoalesceHeuristic.hpp>
#include <umpire/strategy/QuickPool.hpp>

#include <algorithm>
#include <vector>

constexpr auto initial_block_bytes = (1 << 30);
constexpr auto next_block_bytes = (1 << 30);
constexpr auto coalescing_free_ratio = 1.0;
constexpr auto coalescing_reallocation_ratio = 1.0;

// Simulate matrix size
constexpr auto matrix_size = 20000;
constexpr auto bytes_matrix = matrix_size * matrix_size * sizeof(double);

using PoolType = umpire::strategy::QuickPool;
using CoalesceHeuristicType = umpire::strategy::PoolCoalesceHeuristic<PoolType>;

static CoalesceHeuristicType
get_coalesce_heuristic(double coalesce_free_ratio,
                       double coalesce_reallocation_ratio) {
  return [=](const umpire::strategy::QuickPool &pool) {
    std::size_t threshold =
        static_cast<std::size_t>(coalesce_free_ratio * pool.getActualSize());
    if (pool.getReleasableBlocks() >= 2 &&
        pool.getReleasableSize() >= threshold) {
      return static_cast<std::size_t>(coalesce_reallocation_ratio *
                                      pool.getActualSize());
    } else {
      return static_cast<std::size_t>(0);
    }
  };
}

auto main(int argc, char **argv) -> int {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << "<block_size> <alignment_bytes>"
              << std::endl;
    return 1;
  }

  const auto block_size = std::atoi(argv[1]);
  const auto alignment_bytes = std::atoi(argv[2]);

  const auto num_allocations_unknown =
      matrix_size * matrix_size / block_size / block_size;
  const auto bytes_unknown = block_size * block_size * sizeof(double);

  auto &rm = umpire::ResourceManager::getInstance();

  auto device_allocator = rm.getAllocator("DEVICE");
  auto pooled_device_allocator = rm.makeAllocator<PoolType>(
      "POOLED_DEVICE", device_allocator, initial_block_bytes, next_block_bytes,
      alignment_bytes,
      get_coalesce_heuristic(coalescing_free_ratio,
                             coalescing_reallocation_ratio));

  std::cout << "EXPECTED total allocation:\t" << std::fixed
            << std::setprecision(2)
            << (bytes_matrix + num_allocations_unknown * bytes_unknown) / 1e9
            << " GB" << std::endl;

  std::cout << "Allocating " << 1 << " block of " << bytes_matrix
            << " bytes on DEVICE" << std::endl;

  auto d_ptr_matrix = pooled_device_allocator.allocate(bytes_matrix);

  std::cout << "Allocated " << bytes_matrix << " bytes on DEVICE" << std::endl;

  std::vector<void *> d_ptrs(num_allocations_unknown, nullptr);

  std::cout << "Allocating " << num_allocations_unknown << " blocks of "
            << bytes_unknown << " bytes on DEVICE" << std::endl;

  std::for_each(d_ptrs.begin(), d_ptrs.end(), [&](auto &ptr) {
    ptr = pooled_device_allocator.allocate(bytes_unknown);
  });

  std::cout << "Allocated " << num_allocations_unknown * bytes_unknown
            << " bytes on DEVICE" << std::endl;

  std::cout << "UMPIRE pooled_device_allocator size:\t" << std::fixed
            << std::setprecision(2)
            << pooled_device_allocator.getCurrentSize() / 1e9 << " GB"
            << std::endl;

  std::cout << "UMPIRE pooled_device_allocator actual size:\t" << std::fixed
            << std::setprecision(2)
            << pooled_device_allocator.getActualSize() / 1e9 << " GB"
            << std::endl;

  // Possible double counting of DEVICE and DEVICE:0
  std::cout << "UMPIRE total allocation:\t" << std::fixed
            << std::setprecision(2) << umpire::get_total_bytes_allocated() / 1e9
            << " GB" << std::endl;

  sleep(30);

  std::for_each(d_ptrs.begin(), d_ptrs.end(),
                [&](auto &ptr) { pooled_device_allocator.deallocate(ptr); });

  pooled_device_allocator.deallocate(d_ptr_matrix);

  return 0;
}
