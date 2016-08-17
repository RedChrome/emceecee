#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_sf_pow_int.h>
#include <iostream>
#include "../src/position.h"
#include "../src/function.h"
#include "../src/MHSampler.h"

class Rosenbrock: public virtual emceecee::Function {
	public:
		Rosenbrock(double a1, double a2) : a1_(a1), a2_(a2) {

		}

		double evaluate(emceecee::Position const * v) {
			double x = gsl_vector_get(v->position, 0);
			double y = gsl_vector_get(v->position, 1);

			return -( gsl_sf_pow_int(a1_ * (y - x * x), 2) + gsl_sf_pow_int((1- x), 2) ) / a2_;			
		}

	private:
		double a1_, a2_;

};

int main(int argc, char * argv[]) {
//	std::cout << "Hello" << std::endl;

	Rosenbrock * lnprob = new Rosenbrock(100.0, 20.0);
	emceecee::Position * pos = new emceecee::Position(2);
	//pos->position = gsl_vector_alloc(2);
	gsl_vector_set(pos->position, 0, 5);
	gsl_vector_set(pos->position, 1, 5);
//	std::cout << lnprob->evaluate(pos) << std::endl;	
//	std::cout << pos->str() << std::endl;	

	gsl_rng * rng = nullptr;
	gsl_matrix * cov = gsl_matrix_alloc(2, 2);
	gsl_matrix_set_identity(cov);

	emceecee::MHSampler * sampler = new emceecee::MHSampler(2, lnprob, cov, rng);
//	emceecee::MCMCResult * result = sampler->runMCMC(pos, 500);

	emceecee::MHSampler::iterator it = sampler->begin(pos);
//	sampler->next();
//	emceecee::MCMCResult result = 0;

	for(;it != sampler->end(500); it++) {
		emceecee::MCMCResult result = *it;
//		std::cout << it->pos.str() << std::endl;
		std::cout << sampler->current_iterator_result->pos.str() << std::endl;
	}

//	std::cout << result->pos.str() << std::endl;
	
	return 0;
}
