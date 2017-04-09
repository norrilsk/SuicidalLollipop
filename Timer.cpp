
#include "Timer.hpp"

double Timer::count()
{
	high_resolution_clock::time_point t0 = high_resolution_clock::now();
	return duration_cast<duration<double>>(t0 - time).count();
}

void Timer::restart()
{
	time = high_resolution_clock::now();
}

Timer::Timer()
{

}

Timer::~Timer()
{

}
