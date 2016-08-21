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
#include <iostream>
namespace emceecee {

MHSampler::MHSampler(int dimension, Function * lnprob, gsl_matrix const * cov, gsl_rng * rng) :
		GMHSampler(dimension, lnprob, nullptr, this->rng) {
	this->cov = cov;
	// note that we need a working this->rng, since the given one (rng), may be a null ptr
	// and this->rng will be created in GHMSampler if neccessary.
	this->set_proposal(new proposal::NormalDistribution(this->rng, dimension, cov));
}
MHSampler::~MHSampler() {
}


} /* namespace emceecee */
