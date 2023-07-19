#include <hdf5.h>

#include <array>
#include <string>

using namespace std::string_literals;

// type wrapper for esasy conversion from C++ types to HDF5 types
template <typename T> struct hdf5_type_wrapper;

// hdf5_type_wrapper specializations
template <> struct hdf5_type_wrapper<double> {
  operator hid_t() const noexcept { return H5T_NATIVE_DOUBLE; }
};

template <> struct hdf5_type_wrapper<int> {
  operator hid_t() const noexcept { return H5T_NATIVE_INT; }
};

/// Add attribute
///
/// @remark The attribute data space is assumed to be SCALAR
///
/// @param parent_id ID of the parent to which the attribute is added
/// @param name Name of the attribute
/// @param data Data of the attribute
/// @return ID of the new attribute
template <typename T>
hid_t add_attribute(hid_t parent_id, const std::string &name, const T &data) {
  hid_t dataspace_id = H5Screate(H5S_SCALAR);

  hid_t id = H5Acreate(parent_id, name.c_str(), hdf5_type_wrapper<T>(),
                       dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
  herr_t status = H5Awrite(id, hdf5_type_wrapper<T>(), &data);

  return id;
}

/// Add string attribute
///
/// @remark String attribute need to speficy the size of the string
template <>
hid_t add_attribute(hid_t parent_id, const std::string &name,
                    const std::string &data) {
  // Create new string type of given length
  hid_t string_type;
  string_type = H5Tcopy(H5T_FORTRAN_S1); // Copy existing data-type
  herr_t status = H5Tset_size(string_type, std::size(data)); // Set string size

  hid_t dataspace_id = H5Screate(H5S_SCALAR);

  hid_t id = H5Acreate(parent_id, name.c_str(), string_type, dataspace_id,
                       H5P_DEFAULT, H5P_DEFAULT);
  status = H5Awrite(id, string_type, data.c_str());
  return id;
}

/// Add array attribute
///
/// @remark Array attribute need to speficy the size of the array
///
/// @remark Arrays are assumed to be one-dimensional
template <typename T, std::size_t N>
hid_t add_attribute(hid_t parent_id, const std::string &name,
                    const std::array<T, N> &array) {
  hsize_t array_size = std::size(array);
  hid_t array_type = H5Tarray_create(hdf5_type_wrapper<T>(), 1, &array_size);

  hid_t dataspace_id = H5Screate(H5S_SCALAR);

  hid_t id = H5Acreate(parent_id, name.c_str(), array_type, dataspace_id,
                       H5P_DEFAULT, H5P_DEFAULT);
  herr_t status = H5Awrite(id, array_type, array.data());

  return id;
}

int main() {
  hsize_t dims[2];
  herr_t status;

  hid_t file_id = H5Fcreate("qe.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  // Add attribute to /
  add_attribute(file_id, "gamma_only", ".FALSE."s);
  add_attribute(file_id, "igwx", 4572);
  add_attribute(file_id, "scale_factor", 1.0);
  std::array<double, 3> xk = {0.0, 0.13, 0.10};
  add_attribute(file_id, "xk", xk);

  // Add MillerIndices dataset
  dims[0] = 2;
  dims[1] = 3;
  hid_t dataspace_id_miller = H5Screate_simple(2, dims, nullptr);
  hid_t dataset_id_miller =
      H5Dcreate(file_id, "/MillerIndices", H5T_NATIVE_INT, dataspace_id_miller,
                H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  // Add attributes to MillerIndices dataset
  add_attribute(dataset_id_miller, "doc",
                std::string("Miller Indices of the wave-vectors"));
  std::array<double, 3> bg1 = {0.67, 0.39, -0.0};
  add_attribute(dataset_id_miller, "bg1", bg1);

  // Add evec dataset
  dims[0] = 2;
  dims[1] = 3;
  hid_t dataspace_id_evec = H5Screate_simple(2, dims, nullptr);
  hid_t dataset_id_evec =
      H5Dcreate(file_id, "/evec", H5T_NATIVE_DOUBLE, dataspace_id_evec,
                H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  // Add attribute to evec dataset
  add_attribute(dataset_id_evec, "doc", "Wavefunction, (npwx,nbnd)"s);

  status = H5Fclose(file_id);
}
