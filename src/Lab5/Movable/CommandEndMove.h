#pragma once

#include <vector>
#include <Lab5/ICommand.h>
#include <Lab5/IUObject.h>
#include <Lab5/EmptyCommand.h>
#include <Lab5/Movable/IInjectable.h>

//class CommandEndMove: public ICommand
//{
//private:
//	IUObject& _obj;
//	EmptyCommand _emptyCommand;
//
//public:
//	CommandEndMove(IUObject& obj): _obj(obj){}
//
//	void execute()
//	{
//		_obj.setProperty("moveCommand", static_cast<ICommand*>(&_emptyCommand));
//	}
//};
template <typename T>
class CommandEndMove: public ICommand
{
private:
	IUObject& _obj;
	EmptyCommand _emptyCommand;
	IMovable<T>& _moveAdapt;
	std::vector<T> _zeros;

public:
	CommandEndMove(IUObject& obj, IMovable<T>& moveAdapt): _obj(obj), _moveAdapt(moveAdapt)
	{}

	void execute()
	{
		//ICommand* inj = std::any_cast<ICommand*>(_obj.getProperty("moveCommand"));
		//inj->execute();
		//_obj.setProperty("moveCommand", static_cast<ICommand*>(&_emptyCommand));
		//IInjectable* inj = std::any_cast<IInjectable*>(_obj.getProperty("moveCommand"));
		//inj->inject(_emptyCommand);
		
		_zeros = std::vector<T>(_moveAdapt.getVelocity().size(), 0);
		_moveAdapt.setVelocity(_zeros);
		std::any_cast<IInjectable*>(_obj.getProperty("moveCommand"))->inject(static_cast<ICommand*>(&_emptyCommand));
		
		//_gameQueue.push(std::any_cast<ICommand*>(_object.getProperty(_key)));
	}
};