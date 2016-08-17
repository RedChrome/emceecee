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
#include <gsl/gsl_sf_exp.h>
#include "util.cpp"

namespace emceecee {

MHSampler::MHSampler(int dimension, Function * lnprob, gsl_matrix const * cov,
		gsl_rng * rng) :
		Sampler(dimension, lnprob, rng) {
	this->cov = cov;
	this->q = gsl_vector_alloc(this->dimension);

	current_iterator_result = new MCMCResult(dimension);
	next_iterator_result = new MCMCResult(dimension);
}

MHSampler::~MHSampler() {
	gsl_vector_free(this->q);
}

void MHSampler::sample(Position const * pos0, unsigned int iterations,
		std::list<MCMCResult *> * results) {

	gsl_vector * p = pos0->position;

	Position * newpos = new Position(this->dimension);
	newpos->position = this->q;

	double lnprob = this->lnprob->evaluate(pos0);
	double newlnprob;
	double diff;
	gsl_sf_result diffe;
	int status;
	
	gsl_error_handler_t * old_handler = gsl_set_error_handler_off();

	for (unsigned int i = 0; i < iterations; ++i) {
		this->iterations++;

		// Calculate proposal distribution into q
		rmvnorm(this->rng, this->dimension, p, this->cov, this->q);
		// note that newpos contains the pointer q, and
		// q was updated in the call before.
		newlnprob = this->lnprob->evaluate(newpos);

		diff = newlnprob - lnprob;

		if (diff < 0) {
			//status = gsl_sf_exp_e(diff, &diffe);
			//gsl_sf_exp_e10_e(diff, &diffe);
			
			//if(status == GSL_ERANGE)
			//	diffe.val = 0;			

			//diff = diffe.val - gsl_rng_uniform(this->rng);
			diff = gsl_sf_exp(diff) - gsl_rng_uniform(this->rng);
		}

		if (diff > 0) {
			// p = q
			gsl_vector_memcpy(p, this->q);
			lnprob = newlnprob;
			this->accepted++;
		}

		MCMCResult* result = new MCMCResult(this->dimension);
		result->lnprob = lnprob;
		
		gsl_vector_memcpy(result->pos.position, p);

		results->push_back(result);
	}

	delete newpos;
	gsl_set_error_handler(old_handler);
}

void MHSampler::next() {
	gsl_set_error_handler_off();
	double diff;

	this->iterations++;

	// Calculate proposal distribution into next_pos
	rmvnorm(this->rng, this->dimension, this->current_iterator_result->pos.position, this->cov, this->next_iterator_result->pos.position);
	// evaluate lnprob at proposal position
	this->next_iterator_result->lnprob = this->lnprob->evaluate(&this->next_iterator_result->pos);
//	std::cout << this->current_iterator_result->pos.str() << std::endl;
	diff = this->next_iterator_result->lnprob - this->current_iterator_result->lnprob;
//	std::cout << "cur:  " << this->current_iterator_result->pos.str() << " prob: " << this->current_iterator_result->lnprob << std::endl;
//	std::cout << "next: " << this->next_iterator_result->pos.str() <<    " prob: " << this->next_iterator_result->lnprob << std::endl;
	if (diff < 0) {
		diff = gsl_sf_exp(diff) - gsl_rng_uniform(this->rng);
	}

	if (diff > 0) {
//		std::cout << "assigning..." << std::endl;
//		gsl_vector_memcpy(this->current_iterator_result->pos.position, this->next_iterator_result->pos.position);
//		this->current_iterator_result->pos.assign(this->next_iterator_result->pos);
		this->current_iterator_result->pos = this->next_iterator_result->pos;
		this->current_iterator_result->lnprob = this->next_iterator_result->lnprob;
		this->accepted++;
	}
}

} /* namespace emceecee */
