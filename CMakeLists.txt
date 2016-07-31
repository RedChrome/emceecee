cmake_minimum_required (VERSION 2.6)
project (emceecee)

FIND_PACKAGE(GSL REQUIRED)

include_directories("$[PROJECT_BINARY_DIR}/src")

add_library (emceecee src/position
			src/sampler
			src/function
			src/util
	)	
