#include "mm_cu.h"

#include <stdexcept>

namespace cuda
{
    __global__ void mm_kernel(const double *a, const double *b, double *c, size_t n_rows, size_t n, size_t n_cols)
    {
        auto i = blockIdx.x * blockDim.x + threadIdx.x;
        auto j = blockIdx.y * blockDim.y + threadIdx.y;

        if (i < n_rows && j < n_cols)
        {
            double r = 0.0;
            for (size_t k = 0; k < n; k++)
            {
                r += a[index(i, k, n)] * b[index(k, j, n_cols)];
            }

            c[index(i, j, n_cols)] = r;
        }
    }

    auto mm(const double *a,
            const double *b,
            double *c,
            size_t n_rows, size_t n, size_t n_cols,
            size_t n_threads_per_block, size_t n_blocks) -> void
    {
        double *a_device;
        double *b_device;
        double *c_device;

        auto a_size_bytes = sizeof(double) * n_rows * n;
        auto b_size_bytes = sizeof(double) * n * n_cols;
        auto c_size_bytes = sizeof(double) * n_rows * n_cols;

        cudaMalloc(&a_device, a_size_bytes);
        cudaMalloc(&b_device, b_size_bytes);
        cudaMalloc(&c_device, c_size_bytes);

        cudaMemcpy(a_device, a, a_size_bytes, cudaMemcpyHostToDevice);
        cudaMemcpy(b_device, b, b_size_bytes, cudaMemcpyHostToDevice);

        dim3 threads_per_block(n_threads_per_block, n_threads_per_block);
        dim3 blocks(n_blocks, n_blocks);

        mm_kernel<<<threads_per_block, blocks>>>(a_device, b_device, c_device, n_rows, n, n_cols);
        auto err = cudaGetLastError();
        if (cudaSuccess != err)
        {
            throw std::runtime_error(cudaGetErrorString(err));
        }

        cudaMemcpy(c, c_device, c_size_bytes, cudaMemcpyDeviceToHost);

        cudaFree(a_device);
        cudaFree(b_device);
        cudaFree(c_device);
    }
}
