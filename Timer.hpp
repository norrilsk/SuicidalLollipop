#ifndef _TIMER
#define _TIMER

#include <chrono>
using namespace std::chrono;

class Timer
{
private:
	high_resolution_clock :: time_point time = high_resolution_clock :: now();
public:
	Timer();
	~Timer();
	double count();//возвращает текущее время в секундах
	void restart();//перезапускает таймер
};


#endif //SUICIDALLOLLIPOP_TIMER_HPP
