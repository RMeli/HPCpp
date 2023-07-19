#include "hdf5.h"

#include <string>

int main() {
  hid_t file_id;
  hid_t dataset_id_evec, dataspace_id_evec;
  hid_t attribute_id_evec_doc, dataspace_id_evec_doc, dataset_id_evec_doc;
  hsize_t dims[2];
  herr_t status;

  file_id = H5Fcreate("qe.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  dims[0] = 2;
  dims[1] = 3;
  dataspace_id_evec = H5Screate_simple(2, dims, nullptr);
  dataset_id_evec =
      H5Dcreate(file_id, "/evec", H5T_IEEE_F64LE, dataspace_id_evec,
                H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

  // Create new string type of given length
  hid_t string_type;
  std::string evec_doc = "Wavefunction";
  string_type = H5Tcopy(H5T_FORTRAN_S1); // Copy existing data-type
  status = H5Tset_size(string_type, std::size(evec_doc)); // Set string size

  dataspace_id_evec_doc = H5Screate(H5S_SCALAR);
  dataset_id_evec_doc =
      H5Acreate(dataset_id_evec, "doc", string_type, dataspace_id_evec_doc,
                H5P_DEFAULT, H5P_DEFAULT);

  status = H5Awrite(dataset_id_evec_doc, string_type, "Wavefunction");

  status = H5Fclose(file_id);
}
