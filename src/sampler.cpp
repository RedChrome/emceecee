/*
 * sampler.c++
 *
 *  Created on: 26.07.2016
 *      Author: Alex
 */

#include <gsl/gsl_rng.h>
#include <stdexcept>
#include <exception>
#include <list>
#include "position.h"
#include "function.h"

namespace emceecee {
	
struct MCMCResult {
	Position pos;
	double lnprob;
};

class Sampler {

public:
	Sampler(int dimension, Function * lnprob, gsl_rng * rng = nullptr) {
		this->dimension = dimension;
		this->lnprob = lnprob;
		this->created_rng = false;

		if (!rng) {
			this->rng = gsl_rng_alloc(gsl_rng_mt19937);
			this->created_rng = true;
		}
		this->lastResult = nullptr;
		this->iterations = 0;
		this->accepted = 0;
	}

	virtual ~Sampler(){
		if(this->created_rng)
			gsl_rng_free(rng);
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

	void sample(Position const * pos0, unsigned int iterations, std::list<MCMCResult*> * results);

	MCMCResult * runMCMC(Position const * pos0, unsigned int iterations) {	

		if (!pos0) {
			if (lastResult) {
				throw new std::runtime_error(
						"Cannot have pos0 = nullptr if runMCMC has never been called");
			}

			pos0 = &lastResult->pos;
		}


		std::list<MCMCResult * > * results = new std::list<MCMCResult*>(iterations);

		this->sample(pos0, iterations, results);
		lastResult = results->back();

		// delete all other elements from the list
		for(std::list<MCMCResult*>::iterator it=results->begin(); it != results->end(); ++it) {
			delete *it;
		}

		delete results;

		return lastResult;
	}

protected:
	Function * lnprob;
	int dimension;
	gsl_rng * rng;
	unsigned int accepted;
	unsigned int iterations;
	MCMCResult * lastResult;
	bool created_rng;

};

}
