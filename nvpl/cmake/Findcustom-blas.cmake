if(BLA_VENDOR STREQUAL "NVPL")
	find_package("nvpl_blas" REQUIRED)

	if(BLA_SIZEOF_INTEGER EQUAL 4)
		set(_nvpl_int "_lp64")
	else()
		set(_nvpl_int "_ilp64")
	endif()

	if((BLA_THREAD STREQUAL "OMP") OR (BLA_THREAD STREQUAL "ANY"))
		set(_nvpl_thread "_omp")
	else()
		set(_nvpl_thread "_seq")
	endif()

	if(NOT TARGET "BLAS::BLAS")
		add_library("BLAS::BLAS" INTERFACE IMPORTED)
		target_link_libraries("BLAS::BLAS" INTERFACE "nvpl::blas${_nvpl_int}${_nvpl_thread}")
	endif()
else()
	find_package("BLAS" REQUIRED)
endif()
