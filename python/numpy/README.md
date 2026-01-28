# Importing NumPy in C++

```bash
uv venv
source .venv/bin/activate
uv pip install numpy
deactivate
```

## Working example

```bash
source .venv/bin/activate

cmake -S . -B build -GNinja
cmake --build build

./build/nptest
```

## Failing example

If the code is compiled when the venv is not active
```bash
cmake -S . -B build -GNinja
cmake --build build

source .venv/bin/activate

./build/nptest
```

the following failure is triggered:
```
Traceback (most recent call last):
  File "/home/rmeli/git/oss/HPCpp/python/numpy/.venv/lib/python3.11/site-packages/numpy/_core/__init__.py", line 22, in <module>
    from . import multiarray
  File "/home/rmeli/git/oss/HPCpp/python/numpy/.venv/lib/python3.11/site-packages/numpy/_core/multiarray.py", line 11, in <module>
    from . import _multiarray_umath, overrides
ImportError: PyCapsule_Import could not import module "datetime"

The above exception was the direct cause of the following exception:

Traceback (most recent call last):
  File "<string>", line 1, in <module>
  File "/home/rmeli/git/oss/HPCpp/python/numpy/.venv/lib/python3.11/site-packages/numpy/__init__.py", line 112, in <module>
    from numpy.__config__ import show_config
  File "/home/rmeli/git/oss/HPCpp/python/numpy/.venv/lib/python3.11/site-packages/numpy/__config__.py", line 4, in <module>
    from numpy._core._multiarray_umath import (
  File "/home/rmeli/git/oss/HPCpp/python/numpy/.venv/lib/python3.11/site-packages/numpy/_core/__init__.py", line 83, in <module>
    raise ImportError(msg) from exc
ImportError: 

IMPORTANT: PLEASE READ THIS FOR ADVICE ON HOW TO SOLVE THIS ISSUE!

Importing the numpy C-extensions failed. This error can happen for
many reasons, often due to issues with your setup or how NumPy was
installed.

We have compiled some common reasons and troubleshooting tips at:

    https://numpy.org/devdocs/user/troubleshooting-importerror.html

Please note and check the following:

  * The Python version is: Python 3.11 from "/home/rmeli/git/oss/HPCpp/python/numpy/.venv/bin/python3"
  * The NumPy version is: "2.4.1"

and make sure that they are the versions you expect.

Please carefully study the information and documentation linked above.
This is unlikely to be a NumPy issue but will be caused by a bad install
or environment on your machine.

Original error was: PyCapsule_Import could not import module "datetime"

Traceback (most recent call last):
  File "<string>", line 1, in <module>
NameError: name 'np' is not defined
```
