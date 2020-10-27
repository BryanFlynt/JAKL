/*
 * kernel.hpp
 *
 *  Created on: Mar 23, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_JAKL_KERNEL_KERNEL_HPP_
#define INCLUDE_JAKL_KERNEL_KERNEL_HPP_

#include "jakl/kernel/index.hpp"

JAKL_BEGIN_DEVICE_CODE
namespace jakl {

struct kernel {

    template<std::size_t N>
    static Index<N> make_index(
		const typename Index<N>::size_type i,
		const typename Index<N>::size_type* range_ptr) {
	Index<N> ans;
	ans.set_on_device_(i,range_ptr);
	return ans;
    }

};

} // namespace jakl
JAKL_END_DEVICE_CODE


#endif /* INCLUDE_JAKL_KERNEL_KERNEL_HPP_ */
