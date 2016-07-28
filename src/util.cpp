/*
 * util.cpp
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#ifndef UTIL_CPP_
#define UTIL_CPP_


#include "lib/gsl/matrix/gsl_matrix.h"
#include "lib/gsl/linalg/gsl_linalg.h"
#include "lib/gsl/vector/gsl_vector.h"
#include "lib/gsl/blas/gsl_blas.h"

namespace emceecee {

/* multivariate normal distribution random number generator
 *
 *	n	dimension of the random vetor
 *	mean	vector of means of size n
 *	var	variance matrix of dimension n x n
 *	result	output variable with a sigle random vector normal distribution generation
 */
int rmvnorm(const gsl_rng *r, const int n, const gsl_vector *mean,
		const gsl_matrix *var, gsl_vector *result) {

	int k;
	gsl_matrix *work = gsl_matrix_alloc(n, n);

	gsl_matrix_memcpy(work, var);
	gsl_linalg_cholesky_decomp(work);

	for (k = 0; k < n; k++)
		gsl_vector_set(result, k, gsl_ran_ugaussian(r));

	gsl_blas_dtrmv(CblasLower, CblasNoTrans, CblasNonUnit, work, result);
	gsl_vector_add(result, mean);

	gsl_matrix_free(work);

	return 0;
}

}

#endif
