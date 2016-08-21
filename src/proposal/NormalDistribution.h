/*
 * NormalDistribution.h
 *
 *  Created on: 21.08.2016
 *      Author: Alex
 */

#ifndef PROPOSAL_NORMALDISTRIBUTION_H_
#define PROPOSAL_NORMALDISTRIBUTION_H_

#include "../util.cpp"
#include "Function.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>

namespace emceecee {
namespace proposal {

class NormalDistribution: public virtual Function {
public:
	NormalDistribution(const gsl_rng * rng, const int dimension, const gsl_matrix *cov) : Function(rng, dimension) {
		this->covariance = cov;
	}

	virtual ~NormalDistribution() {
	}

	void propose(const gsl_vector * currentpos, gsl_vector * proposalpos) {
		rmvnorm(rng, dimension, currentpos, covariance, proposalpos);
	}

private:
	const gsl_matrix * covariance;

};

} /* namespace proposal */
} /* namespace emceecee */

#endif /* PROPOSAL_NORMALDISTRIBUTION_H_ */
