import mm
import numpy as np

if __name__ == "__main__":
    a = [[1, 0], [0, 1]]
    b = [[2], [3]]

    c = mm.matmul(a, b)

    print(c)
    
    # Check with NumPy
    a_np = np.array(a)
    b_np = np.array(b)
    c_np = np.matmul(a_np, b_np)
    assert np.array_equal(c, c_np)

    try:
        mm.matmul(b, a)
    except ValueError as e:
        print(f"Caught expected exception: {e}")

    try:
        b = ((2,), (3,))
        mm.matmul(a, b)
    except TypeError as e:
        print(f"Caught expected exception: {e}")


    
