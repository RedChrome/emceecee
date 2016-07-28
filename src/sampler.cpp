/*
 * sampler.c++
 *
 *  Created on: 26.07.2016
 *      Author: Alex
 */

namespace emceecee {

#include "lib/gsl/rng/gsl_rng.h"
#include <exception>
#include <list>

struct MCMCResult {
	Position pos;
	double lnprob;
};

class Sampler {

public:
	Sampler(int dimension, Function * lnprob, gsl_rng * rng = nullptr) {
		this->dimension = dimension;
		this->lnprob = lnprob;

		if (!rng) {
			this->rng = gsl_rng_alloc(gsl_rng_mt19937);
		}
		this->lastResult = nullptr;
		this->iterations = 0;
		this->accepted = 0;
	}

	void setRandomNumberGenerator(gsl_rng * rng) {
		this->rng = rng;
	}

	gsl_rng * getRandomNumberGenerator() {
		return this->rng;
	}

	double getAcceptanceFraction() {
		return ((double) this->accepted) / this->iterations;
	}

	void reset() {
		this->iterations = 0;
		this->accepted = 0;
	}

	std::list<MCMCResult *>* sample(Position * pos0, unsigned int iterations);

	MCMCResult * runMCMC(Position * pos0, unsigned int iterations) {
		if (!pos0) {
			if (lastResult) {
				throw new std::runtime_error(
						'Cannot have pos0 = nullptr if runMCMC has never been called');
			}

			pos0 = lastResult->pos;

		}

		std::list<MCMCResult *> result = this->sample(pos0, iterations);
		lastResult = result->back();

		return lastResult;
	}

private:
	Function * lnprob;
	int dimension;
	gsl_rng * rng;
	unsigned int accepted;
	unsigned int iterations;
	MCMCResult * lastResult;

};

}
