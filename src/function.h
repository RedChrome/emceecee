/*
 * function.h
 *
 *  Created on: 26.07.2016
 *      Author: Alex
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

namespace emceecee {

class Function {
	public:
		virtual double evaluate(Position const * x) = 0;
};

}

#endif /* FUNCTION_H_ */
