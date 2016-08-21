/*
 * Function.h
 *
 *  Created on: 21.08.2016
 *      Author: Alex
 */

#ifndef PROPOSAL_FUNCTION_H_
#define PROPOSAL_FUNCTION_H_

#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>

namespace emceecee {
namespace proposal {

class Function {
public:
	Function(const gsl_rng * _rng, const int _dimension) : rng(_rng), dimension(_dimension){
	}
	virtual ~Function() {
	}
	virtual void propose(const gsl_vector * currentpos, gsl_vector * proposalpos) = 0;

protected:
	const gsl_rng * rng;
	const int dimension;
};

} /* namespace proposal */
} /* namespace emceecee */

#endif /* PROPOSAL_FUNCTION_H_ */
