#define Py_LIMITED_API 0x030A0000 // Python 3.10 C API
#define PYSSIZE_T_CLEAN
#include <Python.h>

// Function to perform matrix multiplication
static PyObject* mm_matmul(PyObject* self, PyObject* args){
    // Parse arguments: expects two Python lists of lits (2D matrices)
    PyObject *a_obj, *b_obj;
    if (!PyArg_ParseTuple(args, "OO", &a_obj, &b_obj)) {
        return NULL;
    }
    
    // Check that both arguments are Python lists
    if (!PyList_Check(a_obj) || !PyList_Check(b_obj)) {
        PyErr_SetString(PyExc_TypeError, "Both arguments must be lists");
        return NULL;
    }

    // Get dimensions of the matrices
    Py_ssize_t a_rows = PyList_Size(a_obj);
    Py_ssize_t a_cols = PyList_Size(PyList_GetItem(a_obj, 0));
    Py_ssize_t b_rows = PyList_Size(b_obj);
    Py_ssize_t b_cols = PyList_Size(PyList_GetItem(b_obj, 0));

    // Check if multiplication is possible
    if (a_cols != b_rows) {
        PyErr_SetString(PyExc_ValueError, "Incompatible matrix dimensions for multiplication");
        return NULL;
    }

    // Matrix multiplication working directly with Python objects
    PyObject *result = PyList_New(a_rows);
    for (Py_ssize_t i = 0; i < a_rows; i++){
        PyObject *row = PyList_New(b_cols);
        for (Py_ssize_t j = 0; j < b_cols; j++){
            // Create new Python integer for sum
            PyObject *sum = PyLong_FromLong(0);
            for (Py_ssize_t k = 0; k < a_cols; k++){
                // Extract matrix elements (ik and kj)
                PyObject *a_ik = PyList_GetItem(PyList_GetItem(a_obj, i), k);
                PyObject *b_kj = PyList_GetItem(PyList_GetItem(b_obj, k), j);

                // Multiply matrix elemnts and add them to sum
                // PyNumber_Add and PyNumber_Multiply return new object
                // The new object is assigned to new_sum to avoid memory leaks
                // The reference count of sum and prod is decremented after use
                PyObject *prod = PyNumber_Multiply(a_ik, b_kj);
                PyObject *new_sum = PyNumber_Add(sum, prod);
                Py_DECREF(sum);
                Py_DECREF(prod);

                // Update sum to new_sum (the previous sum has been freed by reference count decrement)
                sum = new_sum;
            }
            PyList_SetItem(row, j, sum);
        }
        PyList_SetItem(result, i, row);
    }

    return result;
}

static PyMethodDef mm_methods[] = {
    {"matmul", mm_matmul, METH_VARARGS, "Multiply two matrices."},
    {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef mm_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "mm",
    .m_methods = mm_methods
};

PyMODINIT_FUNC PyInit_mm(void){
    // Return new module object of type PyObject*
    // Initializes PyModuleDef and PyMethodDef structures
    return PyModule_Create(&mm_module);
}