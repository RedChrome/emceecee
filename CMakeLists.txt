cmake_minimum_required (VERSION 2.6)
project (emceecee)

FIND_PACKAGE(GSL REQUIRED)

include_directories("$[PROJECT_BINARY_DIR}/src")

add_library (emceecee src/position
			src/sampler
			src/function
			src/util
			src/MHSampler
			src/GMHSampler
	)	

add_executable (test_rosenbrock tests/rosenbrock)

target_link_libraries (test_rosenbrock emceecee ${GSL_LIBRARIES})
