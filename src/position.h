/*
 * position.h
 *
 *  Created on: 26.07.2016
 *      Author: Alex
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <vector>
#include <gsl/gsl_vector.h>
#include <string>
#include <sstream>

namespace emceecee {

class Position {
public:
	//int getDimension();
	gsl_vector * position;
	//std::vector<double> position;
	
	Position(int dimension) {
		position = gsl_vector_alloc(dimension);
	}
	
	Position(gsl_vector * position)
	{
		this->position = position;
	}

	Position& operator=(Position rhs)
	{
		gsl_vector_memcpy(position, rhs.position);
		return *this;
	}

	std::string str() const {
		std::stringstream ss;
		ss << "[";
		size_t length = position->size;
		for(int i = 0; i < length - 1; i++) {
			ss << gsl_vector_get(position, i) << ", "; 
		}

		ss << gsl_vector_get(position, length - 1);

		ss << "]";

		return ss.str();
	}

};

}

#endif /* POSITION_H_ */
