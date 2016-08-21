#/*
 * MHSampler.cpp
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#include "MHSampler.h"
#include <list>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include "util.cpp"

namespace emceecee {

MHSampler::MHSampler(int dimension, Function * lnprob, gsl_matrix const * cov, gsl_rng * rng) :
		GMHSampler(dimension, lnprob, this->normaldistributionproposal, this->rng) {
	this->cov = cov;
}

void MHSampler::normaldistributionproposal(const gsl_rng * rng, const int dimension, const gsl_vector * currentpos, gsl_vector * proposalpos) {
	rmvnorm(rng, dimension, currentpos, this->cov, proposalpos);
}


} /* namespace emceecee */
