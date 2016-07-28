/*
 * position.h
 *
 *  Created on: 26.07.2016
 *      Author: Alex
 */

#ifndef POSITION_H_
#define POSITION_H_

namespace emceecee {

#include <vector>

class Position {
public:
	//int getDimension();
	gsl_vector * position;
	//std::vector<double> position;
};

}

#endif /* POSITION_H_ */
