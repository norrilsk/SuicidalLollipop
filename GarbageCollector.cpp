#include "GarbageCollector.hpp"

GarbageCollector::~GarbageCollector()
{
	clean();
}

void GarbageCollector::clean()
{
	for(std::function<void()> f : fun0)
		f();
	for(std::pair<std::function<void(int)>, size_t>f1 : fun1)
		f1.first(f1.second);
}
