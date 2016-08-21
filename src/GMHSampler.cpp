/*
 * GMHSampler.cpp
 *
 *  Created on: 21.08.2016
 *      Author: Alex
 */

#include "GMHSampler.h"
#include <list>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_sf_exp.h>
#include "util.cpp"

namespace emceecee {

GMHSampler::GMHSampler(int dimension, Function * lnprob, MHProposalFunction proposalfct, gsl_rng * rng) :
		Sampler(dimension, lnprob, rng) {
	this->q = gsl_vector_alloc(this->dimension);
	this->proposalfct = proposalfct;
	current_iterator_result = new MCMCResult();
	next_iterator_result = new MCMCResult();
}

GMHSampler::~GMHSampler() {
	gsl_vector_free(this->q);
	delete current_iterator_result, next_iterator_result;
}

void GMHSampler::sample(Position const * pos0, unsigned int iterations, std::list<MCMCResult *> * results) {
	gsl_vector * p = pos0->position;

	Position * newpos = new Position;
	newpos->position = this->q;

	double lnprob = this->lnprob->evaluate(pos0);
	double newlnprob;
	double diff;

	for (unsigned int i = 0; i < iterations; ++i) {
		this->iterations++;

		// Calculate proposal distribution into q
		proposalfct(this->rng, this->dimension, p, this->q);

		//rmvnorm(this->rng, this->dimension, p, this->cov, this->q);
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

	delete newpos;
}

void GMHSampler::next() {
	double diff;

	this->iterations++;

	// Calculate proposal distribution into next_pos
	proposalfct(this->rng, this->dimension, this->current_iterator_result->pos.position, this->next_iterator_result->pos.position);

	// evaluate lnprob at proposal position
	this->next_iterator_result->lnprob = this->lnprob->evaluate(&this->next_iterator_result->pos);

	diff = this->next_iterator_result->lnprob - this->current_iterator_result->lnprob;

	if (diff < 0) {
		diff = gsl_sf_exp(diff) - gsl_rng_uniform(this->rng);
	}

	if (diff > 0) {
		gsl_vector_memcpy(this->current_iterator_result->pos.position, this->next_iterator_result->pos.position);
		this->current_iterator_result->lnprob = this->next_iterator_result->lnprob;
		this->accepted++;
	}
}

} /* namespace emceecee */
