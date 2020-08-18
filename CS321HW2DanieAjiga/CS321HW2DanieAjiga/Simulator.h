
#pragma once
#ifndef AIRPORT
#define AIRPORT
namespace airspace
{
	class bool_source
	{
	private:
		double probability; // probability of a plane arriving or about take off
	public:
		//constructor
		bool_source(double p = 0.5);
		//constant member function
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
		void set_time(unsigned int y);
		void onesecond();
		void use_runway();
		bool is_busy() const { return (action_time_left > 0); };
	};

}
#endif
#pragma once