enum ErrorType
{
	NONE,
	SDL,
	OTHER
};

class Error
{
	ErrorType type;
	public:
	Error(ErrorType er);
	Error();
	ErrorType getType() {return type;}
}; 
