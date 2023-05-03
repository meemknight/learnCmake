#include <Windows.h>
#include <iostream>

#include "profilerLib/profilerLib.h"


int main()
{
	//how to use the profiler
	PL::Profiler profiler;

	profiler.start();

	Sleep(1000);

	auto r = profiler.end();

	std::cout << r.timeSeconds << "  " << r.cpuClocks << "\n";


	//the average profiler can run multiple tests and average then.
	PL::AverageProfiler aProfiler;

	for(int i=0;i<5;i++)
	{
		aProfiler.start();
		Sleep(1000);
		aProfiler.end();
	}
	

	//you can also use aProfiler.getAverageNoResetData and not reset the data
	r = aProfiler.getAverageAndResetData();
	std::cout << r.timeSeconds << "  " << r.cpuClocks << "\n";


	return 0;
}