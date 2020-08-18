#include "pch.h"
#include <cassert>//Provides assert
#include <cstdlib>//provides rand, RAND_MAX, size_t
#include "Simulator.h"//provides bool_source, averager, runway definitions

namespace airspace
{
	bool_source::bool_source(double p)
	{
		assert(p >= 0);
		assert(p <= 1);
		probability = p;
	}


	bool bool_source::query() const                 //constant member function
	{
		return (rand() < probability * RAND_MAX);
	}

	averager::averager()
	{
		count = 0;
		sum = 0;
	}
	void averager::next_number(double value)
	{
		++count;
		sum += value;
	}

	double averager::average() const
	{
		if (how_many_numbers() > 0)
			return sum / count;
		else
			return 0;
	}

	runway::runway()                                  //function for time passing
	{
		seconds_for_action = 0;
		action_time_left = 0;
	}
	void runway::set_time(unsigned int y)
	{
		seconds_for_action = y;
		action_time_left = 0;
	}
	void runway::onesecond()
	{
		if (is_busy())
			--action_time_left;
	}
	void runway::use_runway()
	{
		action_time_left = seconds_for_action;
	}
}