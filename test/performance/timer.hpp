/*
 * timer.hpp
 *
 *  Created on: Apr 22, 2019
 *      Author: bryan.flynt
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <cstdlib>
#include <ctime>
#include <chrono>

namespace xstd {

// After doing a lot of reading this is what I found
//
// In all implementation high_resolution_clock is a typedef to
// system_clock OR steady_clock.
//
// system_clock - Wall clock time from the system-wide realtime clock.
// This clock is NOT steady since an update from a NTP server could
// reset the time while the program is running.
//
// steady_clock - Clocks for which values of time_point never decrease
// as physical time advances and for which values of time_point advance
// at a steady rate relative to real time.
//
// clock() - Reports CPU time which is the sum of all threads CPU time.
// This clock is found within the header <ctime>.  i.e.
// double dt = (double(finish-start)/CLOCKS_PER_SEC);
//

/**
 * @brief
 * Detect the highest resolution clock between the system and steady
 */
using maxres_sys_or_steady =
		std::conditional<
		std::chrono::steady_clock::period::den <= std::chrono::system_clock::period::den,
		std::chrono::steady_clock, std::chrono::system_clock>::type;

/**
 * @brief
 * Detect the highest resolution non-sleeping clock
 */
using maxres_nonsleep_clock =
		std::conditional<
		std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock, maxres_sys_or_steady>::type;

/**
 * @brief Timer struct to time events
 *
 * Timer to provide an uniform timer for all events.
 */
class Timer final {
public:

	void start() {
		start_ = this->now();
	}

	void stop() {
		stop_ = this->now();
	}

	double elapsed_seconds() const {
		auto secs = std::chrono::duration<double>(stop_ - start_);
		return secs.count();
	}

protected:
	using clock_type = maxres_nonsleep_clock;
	using time_point = clock_type::time_point;

	time_point start_;
	time_point stop_;

	time_point now(){
		return clock_type::now();
	}
};



} /* namespace xstd */


#endif /* TIMER_HPP_ */
