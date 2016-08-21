#/*
 * MHSampler.cpp
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#include "MHSampler.h"
#include "GMHSampler.h"
#include <list>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include "util.cpp"

namespace emceecee {

void MHSampler::normaldistributionproposal(const gsl_rng * rng, const int dimension, const gsl_vector * currentpos, gsl_vector * proposalpos) {
	rmvnorm(rng, dimension, currentpos, this->cov, proposalpos);
}

MHSampler::MHSampler(int dimension, Function * lnprob, gsl_matrix const * cov, gsl_rng * rng) :
		GMHSampler(dimension, lnprob, nullptr, this->rng) { //MHSampler::normaldistributionproposal, this->rng) {
	this->cov = cov;
	this->set_proposal(MHSampler::normaldistributionproposal);	
}

MHSampler::~MHSampler() {
}


} /* namespace emceecee */
