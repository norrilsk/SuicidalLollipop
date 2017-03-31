#ifndef _Error
	#define _Error

#include <string>
#define newError(a) Error((a), __FILE__, __LINE__)//подставляющий имя файла и сторку
#define newError2(a,b) Error((a), (b), __FILE__, __LINE__)//подставляющий имя файла и сторку
enum ErrorType
	{
		NONE,
		SDL,
		GL,
		OTHER,
		UNKNOWN,
		QUIT,
		SHADER,
		LOGFILE,
		BINDING_UNLOADED
	};

	class Error
	{
		ErrorType type;
        int line;
        std::string file;
        std::string meta;
		std::string get_glInfo();//Информация об ошибке gl;
		public:
		Error(ErrorType, const char *, int); //тип ошибки, имя файла, строка (последние 2 генерируются макросом newError)
        Error(ErrorType, std::string, const char *, int);//тип ошибки, информация о ней, имя файла, строка (последние 2 генерируются макросом newError2)
		Error();
        std::string getMessage();
		ErrorType getType() {return type;}
	}; 
#endif
