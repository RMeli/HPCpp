
#include <pika/execution.hpp>
#include <pika/init.hpp>
#include <pika/runtime.hpp>

#include <iostream>

constexpr int N = 1e6;
constexpr int n = 1e2;

int main() {
  for (int i = 0; i < N; i++) {
    if (i % n == 0) {
      std::cerr << "Restart #" << i << '\n';
    }
    pika::start(nullptr, 0, nullptr);
    pika::finalize();
    pika::stop();
  }
}
