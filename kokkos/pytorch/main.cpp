#include <Kokkos_Core.hpp>
#include <torch/torch.h>

#include <iostream>

int main(int argc, char** argv) {

  constexpr int n = 5;

  Kokkos::initialize(argc, argv);
  {
    using KokkosMemory = Kokkos::CudaSpace;
    //using KokkosMemory = Kokkos::CudaUVMSpace;
    //using KokkosMemory = Kokkos::HostSpace;

    // Allocate view on CUDA device memory
    Kokkos::View<int*, KokkosMemory> v1("v", n);
    Kokkos::View<int*, KokkosMemory> v2("v", n);
    
    // Fill view with sequentially increasing values
    Kokkos::parallel_for("fill", n, KOKKOS_LAMBDA(int i) { v1(i) = i; });
    Kokkos::parallel_for("fill", n, KOKKOS_LAMBDA(int i) { v2(i) = -i; });

    // Modify v2 on the CPU
    // Fails with Kokkos::CudaSpace
    // Works with Kokkos::CudaUVMSpace
    v2(0) = 42;

    auto t1 = torch::from_blob(v1.data(), {n}, torch::TensorOptions().dtype(torch::kInt32).device(torch::kCUDA));
    auto t2 = torch::from_blob(v2.data(), {n}, torch::TensorOptions().dtype(torch::kInt32).device(torch::kCUDA));

    auto t3 = t1 + t2;

    std::cout << "t3 =\n" << t3 << '\n';

    auto t1_h = t1.cpu();
    auto t2_h = t2.cpu();
    auto t3_h = t3.cpu();

    std::cout << "t1_h =\n" << t1_h << '\n';
    std::cout << "t2_h =\n" << t2_h << '\n';
    std::cout << "t3_h =\n" << t3_h << '\n';
  }
  Kokkos::finalize();
  return 0;
}
