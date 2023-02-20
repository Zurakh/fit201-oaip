#pragma once

#include <iostream>
#include <vector>
#include <Lab5/ICommand.h>
#include "CommandMove.h"
#include <Lab5/IUObject.h>
#include <Lab5/IGameQueue.h>
#include "IMovable.h"

template <typename T>
class CommandStartMove: public ICommand
{

private:
	IUObject& _object;
	IGameQueue& _gameQueue;
	IMovable<T>& _moveAdapt;
	std::vector<T>& _velocity;
	std::vector<T> _zeros;

public:
	CommandStartMove(IUObject& object, IGameQueue& gameQueue, IMovable<T>& moveAdapt, std::vector<T>& velocity):
		_object(object), _moveAdapt(moveAdapt), _gameQueue(gameQueue), _velocity(velocity)
	{
		_zeros = std::vector<T>(velocity.size(), 0);

		ICommand* moveComPtr = this;
		_object.setProperty("moveCommand", moveComPtr);
	}

	void execute()
	{
		_moveAdapt.setVelocity(_velocity);
		CommandMove<T> movCmd(_moveAdapt);
		movCmd.execute();
		_moveAdapt.setVelocity(_zeros);

		_gameQueue.push(std::any_cast<ICommand*>(_object.getProperty("moveCommand")));
	}
};