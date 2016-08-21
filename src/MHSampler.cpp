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
#include "proposal/NormalDistribution.h"

namespace emceecee {

MHSampler::MHSampler(int dimension, Function * lnprob, gsl_matrix const * cov, gsl_rng * rng) :
		GMHSampler(dimension, lnprob, nullptr, this->rng) { //MHSampler::normaldistributionproposal, this->rng) {
	this->cov = cov;
	this->proposalfct = new proposal::NormalDistribution(rng, dimension, cov);
}

MHSampler::~MHSampler() {
}


} /* namespace emceecee */
