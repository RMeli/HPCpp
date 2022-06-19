#pragma once

#include <chrono>

using duration = std::chrono::milliseconds;

class Timer{
public:
    void start();
    duration stop();

    bool ticking() const noexcept;

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> ti, tf;
  bool ticking_ = false;
};