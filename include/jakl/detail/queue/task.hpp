/*
 * task.hpp
 *
 *  Created on: Oct 22, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_DETAIL_QUEUE_TASK_HPP_
#define INCLUDE_JAKL_DETAIL_QUEUE_TASK_HPP_


#include "jakl/kernel.hpp"


#include <functional> // std::function
#include <list>       // std::list



namespace jakl {
namespace detail {




class task {


	//-------------------------------------------------------------------------
	// Types & Constants
	//-------------------------------------------------------------------------
public:
	using VoidFunctionWrapper = std::function<void(void)>;

	//-------------------------------------------------------------------------
	// Construction & Destruction
	//-------------------------------------------------------------------------
public:
	task()                             = default;
	task(const task& other)            = default;
	task(task&& other)                 = default;
	task& operator=(const task& other) = default;
	task& operator=(task&& other)      = default;
	~task()                            = default;



	void insert_prelude(VoidFunctionWrapper const& f) {
		pre_kernel_functions_.push_back(f);
	}

	void insert_postlude(VoidFunctionWrapper const& f) {
		post_kernel_functions_.push_back(f);
	}

	void set_kernel(Kernel const& k) {
		kernel_ = k;
	}


	//-------------------------------------------------------------------------
	// Types & Constants [Private]
	//-------------------------------------------------------------------------

	using FunctionList = std::list<VoidFunctionWrapper>;

	//-------------------------------------------------------------------------
	// Data [Private]
	//-------------------------------------------------------------------------
private:

	FunctionList pre_kernel_functions_;  // Functions to be executed before kernel

	FunctionList post_kernel_functions_; // Functions to be executed after kernel

	Kernel kernel_; // Kernel function to be executed

	//-------------------------------------------------------------------------
	// Methods [Private]
	//-------------------------------------------------------------------------

	void execute_prelude_() {
		for(const auto& func : pre_kernel_functions_){
			func();
		}
		pre_kernel_functions_.clear();
	}

	void execute_postlude_() {
		for(const auto& func : post_kernel_functions_){
			func();
		}
		post_kernel_functions_.clear();
	}

	void execute_kernel_() {
		kernel_();
	}

};



} /* namespace detail */
} /* namespace jakl */




#endif /* INCLUDE_JAKL_DETAIL_QUEUE_TASK_HPP_ */
