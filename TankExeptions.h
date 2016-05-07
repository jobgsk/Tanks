#ifndef TANK_EXEPTIONS_H_
#define TANK_EXEPTIONS_H_

#include <iostream>
#include <exception>

class ExitException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Exit pressed";
	}
};

#endif /* TANK_EXEPTIONS_H_ */