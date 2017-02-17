enum ErrorType
{
	NONE,
	SDL,
	OTHER,
	QUIT
};

class Error
{
	ErrorType type;
	public:
	Error(ErrorType er);
	Error();
	ErrorType getType() {return type;}
}; 
