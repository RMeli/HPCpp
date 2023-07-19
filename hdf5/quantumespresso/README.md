# QuantumESPRESSO Wavefunction HDF5 File

## Development
 
Developer environment:

```bash
spack install hdf5
spack load hdf5
spack build-env hdf5 -- bash
```

Compilation:

```bash
cd build
cmake ..
make -j
```

Run:

```
./hdf5_qe
```

## Documentation

* [Content of the HDF5 of wavefunction files](https://gitlab.com/QEF/q-e/-/snippets/1869219)
* [QuantumESRPESSO `qeh5_module.f90`](https://github.com/QEF/q-e/blob/develop/Modules/qeh5_module.f90) (SERIAL)
* [QuantumESPRESSO `hdf5_qe.f90`](https://github.com/QEF/q-e/blob/develop/Modules/hdf5_qe.f90) (PARALLEL)
