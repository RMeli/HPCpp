#include <hip/hip_runtime.h>
#include <iostream>

using namespace std;

int main()
{
    hipDeviceProp_t devProp;
    hipError_t err;

    err = hipInit(0);
    err = hipInit(0); // Test if double init is allowed

    err = hipGetDeviceProperties(&devProp, 0);

    cout << "Device name: " << devProp.name << '\n';
    cout << "Compute capability: " << devProp.major << "." << devProp.minor << '\n';
    cout << "Memory clock rate: " << devProp.memoryClockRate << " kHz\n";
    cout << "Memory bus width: " << devProp.memoryBusWidth << " bits\n";
}
