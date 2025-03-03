find_package("nvpl_scalapack" REQUIRED)

if(BLA_SIZEOF_INTEGER EQUAL 4)
	set(_nvpl_int "_lp64")
else()
	set(_nvpl_int "_ilp64")
endif()

if(NOT TARGET "SCALAPACK::SCALAPACK")
	add_library("SCALAPACK::SCALAPACK" INTERFACE IMPORTED)
	target_link_libraries(
		"SCALAPACK::SCALAPACK" INTERFACE
		"nvpl::blacs${_nvpl_int}_${NVPL_MPI_TYPE}"
		"nvpl::scalapack${_nvpl_int}"
	)
endif()
