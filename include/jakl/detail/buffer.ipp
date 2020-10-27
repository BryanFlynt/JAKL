/*
 * buffer_impl.ipp
 *
 *  Created on: Apr 1, 2020
 *      Author: bflynt
 */



#include "jakl/config/assert.hpp"


namespace jakl {
namespace detail {

template<typename T, std::size_t N>
buffer<T,N>::buffer(pointer host_ptr, const range_type& range)
: host_ptr_(host_ptr),
  range_(range),
  id_of_last_write_(system::host_device()) {

	// Allocate buffer memory on host
	auto dev_ptr = system::allocate_memory(bytes(),id_of_last_write_);
	data_ptrs_[id_of_last_write_] = reinterpret_cast<pointer>(dev_ptr);

	// Copy host data into buffer memory on host
	this->update();
}

template<typename T, std::size_t N>
buffer<T,N>::~buffer() {

	// Copy last written data back to host data
	this->flush();

	// DeAllocate all device pointer memory
	for(auto key_item: data_ptrs_){
		system::free_memory(key_item.second, key_item.first);
	}
}

template<typename T, std::size_t N>
template<access::mode Mode>
typename buffer<T,N>::pointer
buffer<T,N>::get_access(const ID id){

	// If we need space then allocate it
	if constexpr(
			(Mode == access::mode::read)  or
			(Mode == access::mode::write) or
			(Mode == access::mode::read_write) ) {

		if( data_ptrs_.count(id) == 0 ){
			auto ptr = system::allocate_memory(bytes(),id);
			data_ptrs_[id] = reinterpret_cast<pointer>(ptr);
		}
	}
	JAKL_ASSERT(data_ptrs_.count(id));

	// If we need to copy data then do it
	if constexpr(
			(Mode == access::mode::read)  or
			(Mode == access::mode::read_write) ) {

		if( id != id_of_last_write_ ){
			system::memcpy(
					data_ptrs_[id],
					data_ptrs_[id_of_last_write_],
					bytes(),
					id,
					id_of_last_write_);
		}
	}

	// If we write data then flag as most recent
	if constexpr(
			(Mode == access::mode::write)  or
			(Mode == access::mode::read_write) ) {
		id_of_last_write_ = id;
	}

	return data_ptrs_[id];
}

template<typename T, std::size_t N>
template<access::mode Mode>
typename buffer<T,N>::pointer
buffer<T,N>::get_access(const Handler& handle){
	return this->get_access<Mode>(handle.get_device().id());
}

template<typename T, std::size_t N>
void
buffer<T,N>::flush() const {
	system::memcpy(
			host_ptr_,
			data_ptrs_.at(id_of_last_write_),
			bytes(),
			system::host_device(),
			id_of_last_write_);
}

template<typename T, std::size_t N>
void
buffer<T,N>::update() {
	id_of_last_write_ = system::host_device();
	system::memcpy(
			data_ptrs_[id_of_last_write_],
			host_ptr_,
			bytes(),
			id_of_last_write_,
			id_of_last_write_);
}

template<typename T, std::size_t N>
typename buffer<T,N>::size_type
buffer<T,N>::size() const {
	return this->range_.size();
}

template<typename T, std::size_t N>
typename buffer<T,N>::size_type
buffer<T,N>::bytes() const {
	return (this->size() * sizeof(value_type));
}

template<typename T, std::size_t N>
const typename buffer<T,N>::range_type&
buffer<T,N>::range() const{
	return range_;
}


} // namespace detail
} // namespace jakl


