
#pragma once
#ifndef LANDINGFIELD
#define LANDINGFIELD
namespace Alsphatspace
{
	class bool_source
	{
	private:
		double probability; 
	public:
		
		bool_source(double p = 0.5);
		
		bool query() const;
	};

	class averager
	{
	private:
		size_t count;
		double sum;
	public:
		averager();
		void next_number(double value);
		size_t how_many_numbers() const { return count; }
		double average() const;
	};
	class runway
	{
	private:
		unsigned int seconds_for_action;
		unsigned int action_time_left;
	public:
		runway();
		void set_time(unsigned int value);
		void onesecond();
		void use_runway();
		bool is_busy() const { return (action_time_left > 0); };
	};

}
#endif
