#pragma once

#include <vector>
#include <Lab5/ICommand.h>
#include <Lab5/IUObject.h>
#include <Lab5/EmptyCommand.h>

class CommandEndMove: public ICommand
{
private:
	IUObject& _obj;
	EmptyCommand _emptyCommand;

public:
	CommandEndMove(IUObject& obj): _obj(obj){}

	void execute()
	{
		_obj.setProperty("moveCommand", static_cast<ICommand*>(&_emptyCommand));
	}
};