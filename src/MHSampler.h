/*
 * MHSampler.h
 *
 *  Created on: 27.07.2016
 *      Author: Alex
 */

#ifndef MHSAMPLER_H_
#define MHSAMPLER_H_

#include "sampler.cpp"
#include <gsl/gsl_matrix.h>
#include <list>
#include <iterator>

namespace emceecee {

class MHSampler: public virtual Sampler {
public:
	MHSampler(int dimension, Function * lnprob, const gsl_matrix *cov, gsl_rng * rng = nullptr);
	virtual ~MHSampler();
	void sample(Position const * pos0, unsigned int iterations, std::list<MCMCResult *>* results);

	class iterator {
	public:
		typedef iterator self_type;
		typedef MCMCResult value_type;
		typedef MCMCResult& reference;
		typedef MCMCResult* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(pointer ptr, MHSampler * sampler, int iterations = 0, bool limited = true) :
				ptr_(ptr), sampler_(sampler), iterations_(iterations), limited_(limited) {
		}
		self_type operator++() {
			sampler_->next();
			iterations_++;
			return *this;
		}
		self_type operator++(int junk) {
			for (int i = 0; i < junk; i++) {
				sampler_->next();
				iterations_++;
			}
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
		MHSampler * sampler_;
		int iterations_;
		bool limited_;
	};

	class const_iterator {
	public:
		typedef const_iterator self_type;
		typedef MCMCResult value_type;
		typedef MCMCResult& reference;
		typedef MCMCResult* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;
		const_iterator(pointer ptr, MHSampler * sampler, int iterations = 0, bool limited = true) :
				ptr_(ptr), sampler_(sampler), iterations_(iterations), limited_(limited) {
		}
		self_type operator++() {
			sampler_->next();
			iterations_++;
			return *this;
		}
		self_type operator++(int junk) {
			for (int i = 0; i < junk; i++) {
				sampler_->next();
				iterations_++;
			}
			return *this;
		}
		const reference operator*() {
			return *ptr_;
		}
		const pointer operator->() {
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
		MHSampler * sampler_;
		int iterations_;
		bool limited_;
	};

	iterator begin() {
		return iterator(this->current_iterator_result, this);
	}

	iterator end(int iterations = -1) {
		return iterator(this->current_iterator_result, this, iterations, iterations > -1);
	}

	const_iterator begin() const {
		return const_iterator(this->current_iterator_result, this);
	}

	const_iterator end(int iterations = -1) const {
		return const_iterator(this->current_iterator_result, this, iterations, iterations > -1);
	}

protected:
	void next();

private:
	// covariance matrix
	gsl_matrix const * cov;
	// update vector needed to calculate new proposal
	gsl_vector * q;

	MCMCResult * current_iterator_result;
	MCMCResult * next_iterator_result;

};

} /* namespace emceecee */

#endif /* MHSAMPLER_H_ */
