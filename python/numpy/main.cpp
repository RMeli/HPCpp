#include <Python.h>

auto main() -> int {
  Py_Initialize();

  PyRun_SimpleString("import numpy as np");
  PyRun_SimpleString("print(np.__file__)");

  Py_Finalize();

  return 0;
}
