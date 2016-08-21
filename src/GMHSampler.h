/*
 * GMHSampler.h
 *
 *  Created on: 21.08.2016
 *      Author: Alex
 */

#ifndef GMHSAMPLER_H_
#define GMHSAMPLER_H_

#include "sampler.cpp"
#include "sampler.cpp"
#include <gsl/gsl_matrix.h>
#include <list>
#include <iterator>

namespace emceecee {

typedef void (*MHProposalFunction)(const gsl_rng *, const int, const gsl_vector *, gsl_vector *);

class GMHSampler: public Sampler {
public:
	GMHSampler(int dimension, Function * lnprob, MHProposalFunction proposalfct, gsl_rng * rng = nullptr);
	virtual ~GMHSampler();
	void sample(Position const * pos0, unsigned int iterations, std::list<MCMCResult *>* results);

	class iterator {
	public:
		typedef iterator self_type;
		typedef MCMCResult value_type;
		typedef MCMCResult& reference;
		typedef MCMCResult* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(pointer ptr, GMHSampler * sampler, int iterations = 0, bool limited = true) :
				ptr_(ptr), sampler_(sampler), iterations_(iterations), limited_(limited) {
		}
		self_type operator++() {
			sampler_->next();
			++iterations_;
			return *this;
		}
		self_type operator++(int junk) {
			sampler_->next();
			++iterations_;
			return *this;
		}
		reference operator*() {
			return *ptr_;
		}
		pointer operator->() {
			return ptr_;
		}
		bool operator==(const self_type& rhs) {
			return ptr_ == rhs.ptr_ && (iterations_ == rhs.iterations_ && limited_);
		}
		bool operator!=(const self_type& rhs) {
			return ptr_ != rhs.ptr_ || iterations_ != rhs.iterations_ || !limited_;
		}
	private:
		pointer ptr_;
		GMHSampler * sampler_;
		int iterations_;
		bool limited_;
	};

	iterator begin(Position * pos0) {
		this->set_position_for_iterator(pos0);
		return iterator(this->current_iterator_result, this);
	}

	iterator end(int iterations = -1) {
		return iterator(this->current_iterator_result, this, iterations, iterations > -1);
	}

protected:
	void next();
	void set_position_for_iterator(Position * pos0) {
		if (!pos0)
			return;

		this->current_iterator_result->pos = *pos0;
		this->current_iterator_result->lnprob = this->lnprob->evaluate(pos0);
	}

	void set_proposal(MHProposalFunction proposalfct) {
		this->proposalfct = proposalfct;	
	}

private:
	// update vector needed to calculate new proposal
	gsl_vector * q;

	MCMCResult * current_iterator_result;
	MCMCResult * next_iterator_result;
	MHProposalFunction proposalfct;
};

} /* namespace emceecee */

#endif /* GMHSAMPLER_H_ */
