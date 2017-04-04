#ifndef _GARBAGECOLLECTOR
#define _GARBAGECOLLECTOR

#include <vector>
#include <functional>

class GarbageCollector
{
	std::vector <std::function<void()> > fun0;
	std::vector <std::pair <std::function<void(size_t)>, size_t > > fun1;
public:
	template <typename T1, typename T2>
	void add(std::function<T1(T2)> func, T2 param)
	{
		size_t  p = size_t(param);
		fun1.push_back({std::function<void(size_t)>(func), p});
	}

	template <typename T1>
	void add(std::function<T1()> func)
	{
		fun0.push_back(std::function<void()>(func));
	}

	void clean();
	~GarbageCollector();
};


#endif
