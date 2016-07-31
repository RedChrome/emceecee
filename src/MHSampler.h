/*
 * MHSampler.h
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#ifndef MHSAMPLER_H_
#define MHSAMPLER_H_

#include "sampler.cpp"
#include <gsl/gsl_matrix.h>
#include <list>

namespace emceecee {

class MHSampler: public virtual Sampler {
public:
	MHSampler(int dimension, Function * lnprob, const gsl_matrix *cov,
			gsl_rng * rng = nullptr);
	virtual ~MHSampler();
	void sample(Position const * pos0, unsigned int iterations, std::list<MCMCResult *>* results);

private:
	// covariance matrix
	gsl_matrix const * cov;
	// update vector needed to calculate new proposal
	gsl_vector * q;
};

} /* namespace emceecee */

#endif /* MHSAMPLER_H_ */
