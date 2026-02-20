# QuickPool with memory alignment

Small reproducer for [llnl/Umpire#881](https://github.com/llnl/Umpire/issues/881).

When using GPU-aware MPI, communicating a buffer whose size isn't page-aligned results in performance degradation (with Cray MPICH).

Setting the memory alignment of `QuickPool` to the large page size (2MB) on GH200
results in considerable wasted memory when allocations are much smaller than the alignment.

With a small block size in DLA-Future, it is very easy to run out of memory.

## Reproducer

The small reproducer simulates the allocation of a 20k x 20k matrix on a single rank,
plus as many allocations of smaller tiles as needed to cover the full matrix.

This happens in DLA-Future, where the local matrix is allocated and temporary tiles are created for communication.

### Build

```bash
cmake -S . -B build -GNinja
cmake --build build
```

### Run

```bash
build/main <TILES_SIZE> <ALIGNMENT_BYTES>
```

### OOM

```
build/main 64 $((1<<21))
```
