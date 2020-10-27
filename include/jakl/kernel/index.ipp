/*
 * index.ipp
 *
 *  Created on: Mar 17, 2020
 *      Author: bflynt
 */


namespace jakl {


template<std::size_t N>
Index<N>::Index(const size_type i, size_type const* range_data_ptr)
: i_(i), range_(range_data_ptr) {
	this->calc_index_();
}

template<std::size_t N>
typename Index<N>::size_type
Index<N>::operator[](const size_type n) const {
	return index_[n];
}

template<std::size_t N>
template<typename... Args>
typename Index<N>::size_type
Index<N>::operator()(const Args... args) const {
	//static_assert(std::conjunction_v<std::is_integral<Args>...>, "Must be integers");
	static_assert(sizeof...(args) == N);
	size_type dims[] = {static_cast<size_type>(args)...};
	size_type offset = 0;
	size_type stride = 1;
	for(size_type j = N; j--> 0;) {
		offset += dims[j] * stride;
		stride *= range_[j];
	}
	return offset;
}

template<std::size_t N>
void
Index<N>::set_on_device_(const size_type i, size_type const* range_data_ptr){
	i_ = i;
	range_ = range_data_ptr;
	this->calc_index_();
}

template<std::size_t N>
void
Index<N>::calc_index_(){
	size_type fac(1);
	for(size_type j = N; j--> 1;) {
		index_[j] = (i_ / fac) % range_[j];
		fac *= range_[j];
	}
	index_[0] = i_ / fac;
}

} // namespace jakl


