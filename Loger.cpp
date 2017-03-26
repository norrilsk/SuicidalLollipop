#include "Loger.hpp"
#include <ctime>

void Loger::open(const char * path)
{
	out.open(path, std::ofstream::out | std::ofstream::app);
	if(!out.is_open())
	{
		throw(newError(LOGFILE));
	}
    out << "********************LOG STARTED********************" << std::endl;
	time_t rawtime;
	if(time(&rawtime) != -1) //если нам удалось получить текущее время
		out <<"Date and time:"<< ctime(&rawtime); //выводим его
	else
		out <<"Couldn't get current time";//Иначе сообщение о том что не удалсь, ошибку НЕ генерируем
	out <<std::endl;
}

Loger::Loger()
{
}

Loger::~Loger()
{
	if(!out.is_open())
		return;
	out << "--------------------LOG FINISHED-------------------" << std::endl;
	time_t rawtime;
	if(time(&rawtime) != -1)
		out <<"Date and time:"<< ctime(&rawtime);
	else
		out <<"Couldn't get current time";
	out << "\n" <<std::endl;
	out.close();
}

Loger &Loger::operator<<(std::ostream &(*f)(std::ostream &))
{
	out << std::endl;
	return *this;
}



