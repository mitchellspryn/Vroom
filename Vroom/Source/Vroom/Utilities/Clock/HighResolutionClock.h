#ifndef VROOM_SYSTEMCLOCK_H
#define VROOM_SYSTEMCLOCK_H

#include "Clock.h"

class HighResolutionClock : public Clock
{
	public:
		static HighResolutionClock& Get()
		{
			static HighResolutionClock ClockInst;
			return ClockInst;
		};

		virtual std::chrono::high_resolution_clock::time_point GetCurrentTime() override
		{
			return std::chrono::high_resolution_clock::now();
		}

		HighResolutionClock(HighResolutionClock const&) = delete;
		void operator = (HighResolutionClock const&) = delete;
	
	private:
		HighResolutionClock() {};
};



#endif