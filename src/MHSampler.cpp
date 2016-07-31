/*
 * MHSampler.cpp
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#include "MHSampler.h"
#include <list>
#include "lib/gsl/matrix/gsl_matrix.h"
#include "lib/gsl/vector/gsl_vector.h"

namespace emceecee {

MHSampler::MHSampler(int dimension, Function * lnprob, gsl_matrix const * cov,
		gsl_rng * rng = nullptr) :
		Sampler(dimension, lnprob, rng) {
	this->cov = cov;
	this->q = gsl_vector_alloc(this->dimension);
}

MHSampler::~MHSampler() {
	gsl_vector_free(this->q);
}

void MHSampler::sample(Position const * pos0, unsigned int iterations,
		std::list<MCMCResult *> * results) {

	gsl_vector * p = pos0->position;

	Position * newpos = new Position;
	newpos->position = this->q;

	double lnprob = this->lnprob->evaluate(pos0);
	double newlnprob;
	double diff;

	for (unsigned int i = 0; i < iterations; ++i) {
		this->iterations++;

		// Calculate proposal distribution into q
		rmvnorm(this->rng, this->dimension, p, this->cov, this->q);
		// note that newpos contains the pointer q, and
		// q was updated in the call before.
		newlnprob = this->lnprob->evaluate(newpos);

		diff = newlnprob - lnprob;

		if (diff < 0) {
			diff = gsl_sf_exp(diff) - gsl_rng_uniform(this->rng);
		}

		if (diff > 0) {
			// p = q
			gsl_vector_memcpy(p, this->q);
			lnprob = newlnprob;
			this->accepted++;
		}

		MCMCResult* result = new MCMCResult;
		result->lnprob = lnprob;
		gsl_vector_memcpy(result->pos.position, p);

		results->push_back(result);
	}
}

} /* namespace emceecee */
