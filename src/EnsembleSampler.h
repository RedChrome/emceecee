/*
 * EnsembleSampler.h
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#ifndef ENSEMBLESAMPLER_H_
#define ENSEMBLESAMPLER_H_

#include "sampler.cpp"

namespace emceecee {

class EnsembleSampler: public Sampler {
public:
	EnsembleSampler();
	virtual ~EnsembleSampler();
};

}

#endif /* ENSEMBLESAMPLER_H_ */
