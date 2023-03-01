#pragma once

#include <iostream>
#include <vector>
#include <Lab5/ICommand.h>
#include "CommandMove.h"
#include <Lab5/IUObject.h>
#include <Lab5/IGameQueue.h>
#include "IMovable.h"

#include <Lab5/Movable/MacroCommand.h>
#include <Lab5/Movable/CommandRepeateByKey.h>
#include <Lab5/Movable/CommandInjectable.h>
#include <any>

template <typename T>
class CommandStartMove: public ICommand
{

//private:
//	IUObject& _object;
//	IGameQueue& _gameQueue;
//	IMovable<T>& _moveAdapt;
//	std::vector<T>& _velocity;
//	std::vector<T> _zeros;
//
//public:
//	CommandStartMove(IUObject& object, IGameQueue& gameQueue, IMovable<T>& moveAdapt, std::vector<T>& velocity):
//		_object(object), _moveAdapt(moveAdapt), _gameQueue(gameQueue), _velocity(velocity)
//	{
//		_zeros = std::vector<T>(velocity.size(), 0);
//
//		ICommand* moveComPtr = this;
//		_object.setProperty("moveCommand", moveComPtr);
//	}
//
//	void execute()
//	{
//		_moveAdapt.setVelocity(_velocity);
//		CommandMove<T> movCmd(_moveAdapt);
//		movCmd.execute();
//		_moveAdapt.setVelocity(_zeros);
//
//		_gameQueue.push(std::any_cast<ICommand*>(_object.getProperty("moveCommand")));
//	}
//};

private:
	IUObject& _object;
	IGameQueue& _gameQueue;
	IMovable<T>& _moveAdapt;
	std::vector<T>& _velocity;
	//std::vector<T> _zeros;
	IInjectable* inj;

public:
	//CommandInjectable& _injCommand;

	//CommandStartMove(IUObject& object, IGameQueue& gameQueue, IMovable<T>& moveAdapt, std::vector<T>& velocity):
	//	_object(object), _moveAdapt(moveAdapt), _gameQueue(gameQueue), _velocity(velocity),
	//	_injCommand(
	//		CommandInjectable(
	//			//static_cast<ICommand*>(
	//				new MacroCommand(
	//					std::vector<ICommand*>{
	//						new CommandMove<T>(_moveAdapt),
	//						new CommandRepeateByKey("moveCommand", _object, _gameQueue)
	//					}
	//				)
	//			//)
	//		)
	//	)
	//{

	CommandStartMove(IUObject & object, IGameQueue & gameQueue, IMovable<T>&moveAdapt, std::vector<T>&velocity):
			_object(object), _moveAdapt(moveAdapt), _gameQueue(gameQueue), _velocity(velocity)
		{
		
		//_zeros = std::vector<T>(velocity.size(), 0);

		//ICommand* moveComPtr = this;
		//_object.setProperty("moveCommand", moveComPtr);

		//CommandMove<T> movCmd(_moveAdapt);
		//CommandRepeateByKey repeateCommand("moveCommand", _object, _gameQueue);
		//MacroCommand macro(std::vector<ICommand*>{movCmd, repeateCommand});
		//CommandInjectable injCommand();
		//injCommand->inject(static_cast<ICommand*>(&macro));
		//injCommand.inject(macro);
		//_injCommand = injCommand;
	}

	void execute()
	{
		_moveAdapt.setVelocity(_velocity);

		/*CommandMove<T> movCmd(_moveAdapt);
		CommandRepeateByKey repeateCommand("moveCommand", _object, _gameQueue);
		MacroCommand macro(std::vector<ICommand*>{&movCmd, &repeateCommand});
		CommandInjectable injCommand;*/

		/*injCommand.inject(static_cast<ICommand&>(macro));*/
		//_object.setProperty("moveCommand", static_cast<ICommand*>(&_injCommand));

		

		//gameQueue.push(static_cast<ICommand*>(&injCommand));

		//std::any example = _object.getProperty("moveCommand");

		//static_cast<ICommand>(example);
		//static_cast<ICommand*>(example);
		//static_cast<ICommand*>(&example);
		//static_cast<ICommand>(&example);
		
		//static_cast<CommandInjectable>(&example);
		//static_cast<CommandInjectable>(example);
		//static_cast<CommandInjectable*>(&example);

		/*CommandMove<T> *movCmd = new CommandMove<T>(_moveAdapt);
		CommandRepeateByKey *repeateCommand = new CommandRepeateByKey("moveCommand", _object, _gameQueue);
		MacroCommand *macro = new MacroCommand(std::vector<ICommand*>{movCmd, repeateCommand});
		
		CommandInjectable *injCommand = new CommandInjectable;
		injCommand->inject(static_cast<ICommand*>(macro));*/

		//CommandMove<T> movCmd(_moveAdapt);
		//CommandRepeateByKey repeateCommand("moveCommand", _object, _gameQueue);
		//MacroCommand macro(std::vector<ICommand*>{&movCmd, &repeateCommand});

		//CommandInjectable injCommand;
		//injCommand.inject(static_cast<ICommand*>(&macro));

		//inj = injCommand;


		//_object.setProperty("moveCommand", dynamic_cast<ICommand*>(injCommand));

		/*_object.setProperty("moveCommand", dynamic_cast<CommandInjectable*>(
			new CommandInjectable(
				new MacroCommand(
					std::vector<ICommand*>{
						new CommandMove<T>(_moveAdapt),
						new CommandRepeateByKey("moveCommand", _object, _gameQueue)
					}
				)
			)
		));*/

		
		

		//_object.setProperty("moveCommand", static_cast<ICommand*>(injCommand));


		//_gameQueue.push(static_cast<ICommand*>(injCommand));

		_object.setProperty("moveCommand", static_cast<ICommand*>(new CommandInjectable));

		std::any_cast<CommandInjectable*>(_object.getProperty())->inject(
			new MacroCommand(
				std::vector<ICommand*>{
					new CommandMove<T>(_moveAdapt),
					new CommandRepeateByKey("moveCommand", _object, _gameQueue)
				}
			)
		);


		_gameQueue.push(std::any_cast<ICommand*>(_object.getProperty("moveCommand")));
		
		

		
		//_gameQueue.push(std::any_cast<CommandInjectable*>(_object.getProperty("moveCommand")));
	}
};