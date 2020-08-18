// CS321HW2DanieAjiga.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <queue>
#include "Simulator.h"
using namespace std;
using namespace Alsphatspace;

void runway_simulation(unsigned int takeoff_time, unsigned int landing_time, double landing_prob, double takeoff_prob, unsigned int wait_time, unsigned int total_time)
{

	queue<unsigned int> ready_to_land;
	queue<unsigned int> ready_to_takeoff;
	bool_source land(landing_prob);
	bool_source take_off(takeoff_prob);
	unsigned int next;
	averager landing;
	averager takeoff;
	unsigned int current_time;
	runway lane1;
	int crashed = 0;

	for (current_time = 1; current_time <= total_time; ++current_time)
	{

		if (land.query())    
			ready_to_land.push(current_time);


		if (take_off.query())  
			ready_to_takeoff.push(current_time);

		if (!lane1.is_busy())
		{
			if (!ready_to_land.empty())  
			{
				while (!ready_to_land.empty() && current_time - ready_to_land.front() >= wait_time)
				{
					crashed++;
					ready_to_land.pop();
				}
				if (!ready_to_land.empty())
				{
					next = ready_to_land.front();
					ready_to_land.pop();
					lane1.set_time(landing_time);
					landing.next_number(current_time - next);
					lane1.use_runway();
				}
				else if (!ready_to_takeoff.empty()) 
				{
					next = ready_to_takeoff.front();
					ready_to_takeoff.pop();
					lane1.set_time(takeoff_time);
					takeoff.next_number(current_time - next);
					lane1.use_runway();
				}
			}
			else if (!ready_to_takeoff.empty())  
			{
				next = ready_to_takeoff.front();
				ready_to_takeoff.pop();
				lane1.set_time(takeoff_time);
				takeoff.next_number(current_time - next);
				lane1.use_runway();
			}
		}
		lane1.onesecond(); 
	}

	cout << "Number of planes that depatured: " << takeoff.how_many_numbers() << endl;
	cout << "Number of planes that arrived : " << landing.how_many_numbers() << endl;
	cout << "Number of planes crashed: " << crashed << endl;
	cout << "Average time in landing queue: " << landing.average() << endl;
	cout << "Average time in takeoff queue: " << takeoff.average() << endl << endl;
}
int main()
{

	unsigned int takeoff_time;
	unsigned int landing_time;
	double takeoff_prob;
	double landing_prob;
	unsigned int wait_time;
	double arrival_prob;
	unsigned int total_time;

	cout << "Seconds required for depature:";
	cin >> takeoff_time;
	cout << "Seconds required for plane arrival: ";
	cin >> landing_time;
	cout << "Probability of a plane to depart: ";
	cin >> takeoff_prob;
	cout << "Probability of plane to be ready to reach its destination: ";
	cin >> landing_prob;
	cout << "Maximum time plane can stay in the landing queue without crashing: ";
	cin >> wait_time;
	cout << "Total simulation seconds: ";
	cin >> total_time;
	cout << endl;
	runway_simulation(takeoff_time, landing_time, landing_prob, takeoff_prob, wait_time, total_time);

	system("pause");
	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
