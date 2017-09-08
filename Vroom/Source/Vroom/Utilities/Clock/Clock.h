#ifndef VROOM_CLOCK_H
#define VROOM_CLOCK_H

#include <chrono>

class Clock
{
	public:
		/*TODO: Can we do this without specifying clock?*/
		virtual std::chrono::high_resolution_clock::time_point GetCurrentTime() = 0;
		virtual ~Clock() {};
};

#endif