#include <cstdio>
#include <cmath>

auto main() -> int {
    int a = 10;
    int b = 20;

    int c = std::max(a, b);

    std::printf("max(%d, %d) = %d\n", a, b, c);

    return 0;
}
