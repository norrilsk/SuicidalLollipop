#include "Error.hpp"
Error :: Error(ErrorType error)
{
	type = error;
}

Error :: Error()
{
	type = NONE;
}
