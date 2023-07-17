#include <hpx/hpx_start.hpp>
#include <hpx/runtime_local/run_as_hpx_thread.hpp>

#include <iostream>

constexpr int N = 1e6;
constexpr int n = 1e2;

int main(int argc, char *argv[]) {
  for (int i = 0; i < N; i++) {
    if (i % n == 0) {
      std::cerr << "Restart #" << i << '\n';
    }

    hpx::start(nullptr, argc, argv);
    hpx::threads::run_as_hpx_thread([]() { hpx::finalize(); });
    hpx::stop();
  }
}
