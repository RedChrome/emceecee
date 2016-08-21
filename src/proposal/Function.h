/*
 * Function.h
 *
 *  Created on: 21.08.2016
 *      Author: Alex
 */

#ifndef PROPOSAL_FUNCTION_H_
#define PROPOSAL_FUNCTION_H_

namespace emceecee {
namespace proposal {

class Function {
public:
	Function::Function(const gsl_rng * rng, const int dimension) {
		this->rng = rng;
		this->dimension = dimension;
	}
	virtual ~Function();
	virtual void propose(const gsl_vector * currentpos, gsl_vector * proposalpos) = 0;

private:
	const gsl_rng * rng;
	const int dimension;
};

} /* namespace proposal */
} /* namespace emceecee */

#endif /* PROPOSAL_FUNCTION_H_ */
