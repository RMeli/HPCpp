
// User-defined main gets renamed and the real main function is defined by HP
#include <hpx/hpx_main.hpp>

// HPX I/O-streams subsystem extends the standard C++ output streams to work
// in the distributed setting of an HPX application.
#include <hpx/iostream.hpp>

int main() {
  hpx::cout << "Hello World!\n" << std::flush;

  // User-defined main must include a return statement
  return 0;
}
