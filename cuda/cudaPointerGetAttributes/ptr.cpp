#include <cuda_runtime.h>

#include <chrono>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <repetitions>\n";
        return EXIT_FAILURE;
    }

    const long long repetitions = std::atoll(argv[1]);

    constexpr std::size_t bytes = 1 << 21;
    
    void* devicePtr = nullptr;
    cudaMalloc(&devicePtr, bytes);

    cudaPointerAttributes attributes;
    auto start = std::chrono::steady_clock::now();
    for (long long i = 0; i < repetitions; ++i) {
        cudaPointerGetAttributes(&attributes, devicePtr);
    }
    auto stop = std::chrono::steady_clock::now();

    double elapsedSeconds = std::chrono::duration<double>(stop - start).count();

    if(attributes.type == cudaMemoryTypeHost) {
        std::cout << "Host memory:\t";
    } else if(attributes.type == cudaMemoryTypeDevice) {
        std::cout << "Device memory:\t";
    } else if(attributes.type == cudaMemoryTypeManaged) {
        std::cout << "Managed memory:\t";
    } else if(attributes.type == cudaMemoryTypeUnregistered) {
        std::cout << "Unreregistered memory:\t";
    }
    std::cout << elapsedSeconds << " s\n";

    char* hostPtr = new char[bytes];

    start = std::chrono::steady_clock::now();
    for (long long i = 0; i < repetitions; ++i) {
        cudaPointerGetAttributes(&attributes, hostPtr);
    }
    stop = std::chrono::steady_clock::now();

    elapsedSeconds = std::chrono::duration<double>(stop - start).count();

    if(attributes.type == cudaMemoryTypeHost) {
        std::cout << "Host memory:\t";
    } else if(attributes.type == cudaMemoryTypeDevice) {
        std::cout << "Device memory:\t";
    } else if(attributes.type == cudaMemoryTypeManaged) {
        std::cout << "Managed memory:\t";
    } else if(attributes.type == cudaMemoryTypeUnregistered) {
        std::cout << "Unreregistered memory:\t";
    }
    std::cout << elapsedSeconds << " s\n";

    cudaFree(devicePtr);
    delete[] hostPtr;
    return EXIT_SUCCESS;
}
