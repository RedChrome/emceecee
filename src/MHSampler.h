/*
 * MHSampler.h
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#ifndef MHSAMPLER_H_
#define MHSAMPLER_H_

#include "GMHSampler.h"
#include <gsl/gsl_matrix.h>

namespace emceecee {

class MHSampler: public virtual GMHSampler {
public:
	MHSampler(int dimension, Function * lnprob, const gsl_matrix *cov, gsl_rng * rng = nullptr);
	virtual ~MHSampler();

	virtual void normaldistributionproposal(const gsl_rng * rng, const int dimension, const gsl_vector * currentpos, gsl_vector * proposalpos);

private:
	// covariance matrix
	gsl_matrix const * cov;
};

} /* namespace emceecee */

#endif /* MHSAMPLER_H_ */
