# Libint2

Simple example of how to compile the `libint`-provided Hartree-Fock code whit `libint` installed with Spack.

## Spack

### Repo

Add repository to Spack:

```bash
spack repo add spack
```

The repository contains a single package named `libinttest` which specifies the dependencies of this simple example.

### Build Environment

Concretize the environment whose only spec is `libinttest`:

```bash
spack -e . concretize -f
```

Install all the dependencies (gathered from the spec and the package definition):

```bash
spack -e . install --only=dependencies
```

Get a shell within the build environment:

```bash
spack -e . build-env libinttest -- bash
```

## CMake

If in the build environment shell:

```bash
mkdir build && cd build
cmake ..
make -j
```

If outside the build environment shell:

```bash
mkdir build && cd build
spack -e . build-env libinttest -- cmake ..
spack -e . build-env libinttest -- make -j
```

## Run

```bash
./hf.x ../data/h2o.xyz
```
