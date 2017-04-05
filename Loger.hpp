#ifndef _LOGER
#define _LOGER
#include "Error.hpp"
#include <fstream>
class Loger
{
	std::ofstream out;
public:
	Loger();
	~Loger();//закрывает лог

    template <class T>
    Loger& operator<<(T message)//вывод сообщения
    {
        out << message;
        return *this;
    }
	Loger& operator<<(std::ostream& (*f)(std::ostream&));//обработка std::endl
    void open(const char *path);//запускает лог в указаный файл
};
#endif



