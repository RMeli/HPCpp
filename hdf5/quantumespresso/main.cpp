#include "hdf5.h"

#include <array>
#include <string>

/// Add attribute with string type
/// @param parent_id ID of the parent
/// @param name Name of the attribute
/// @param data String to store as the attribute
/// @param pace_type Type of the data space
/// @return ID of the attribute
hid_t add_attribute_string(hid_t parent_id, std::string name, std::string data,
                           H5S_class_t dataspace_type = H5S_SCALAR) {
  // Create new string type of given length
  hid_t string_type;
  string_type = H5Tcopy(H5T_FORTRAN_S1); // Copy existing data-type
  herr_t status = H5Tset_size(string_type, std::size(data)); // Set string size

  hid_t dataspace_id = H5Screate(dataspace_type);

  hid_t id = H5Acreate(parent_id, name.c_str(), string_type, dataspace_id,
                       H5P_DEFAULT, H5P_DEFAULT);
  status = H5Awrite(id, string_type, data.c_str());
  return id;
}

template <std::size_t N>
hid_t add_attribute_array(hid_t parent_id, std::string name,
                          std::array<double, N> &array) {
  hsize_t array_size = std::size(array);
  hid_t array_type = H5Tarray_create(H5T_IEEE_F64LE, 1, &array_size);

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
  add_attribute_string(file_id, "gamma_only", ".FALSE.");
  std::array<double, 3> xk = {0, 0.13, 0.10};
  add_attribute_array(file_id, "xk", xk);

  // Add MillerIndices dataset
  dims[0] = 2;
  dims[1] = 3;
  hid_t dataspace_id_miller = H5Screate_simple(2, dims, nullptr);
  hid_t dataset_id_miller =
      H5Dcreate(file_id, "/MillerIndices", H5T_STD_I32LE, dataspace_id_miller,
                H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  // Add attributes to MillerIndices dataset
  add_attribute_string(dataset_id_miller, "doc",
                       "Miller Indices of the wave-vectors");
  std::array<double, 3> bg1 = {0.67, 0.39, -0.0};
  add_attribute_array(dataset_id_miller, "bg1", bg1);

  // Add evec dataset
  dims[0] = 2;
  dims[1] = 3;
  hid_t dataspace_id_evec = H5Screate_simple(2, dims, nullptr);
  hid_t dataset_id_evec =
      H5Dcreate(file_id, "/evec", H5T_IEEE_F64LE, dataspace_id_evec,
                H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  // Add attribute to evec dataset
  add_attribute_string(dataset_id_evec, "doc", "Wavefunction, (npwx,nbnd)");

  status = H5Fclose(file_id);
}
