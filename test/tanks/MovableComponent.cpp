#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <misc/vectorOps.h>

#include <Lab5/UObject.h>

#include <Lab5/Movable/CommandMove.h>
#include <Lab5/Movable/CommandStartMove.h>
#include <Lab5/Movable/CommandEndMove.h>

#include "mocks/MockMovable.h"
#include "stubs/GameQueueRealization.h"


TEST(Tanks_MovableComponent, BaseMoveCommand)
{
	std::vector<int> position{ 10, 20, 30 };
	const std::vector<int> velocity{ 45, 25, 55 };

	MockMovable<int> mcmv;

	EXPECT_CALL(mcmv, setPosition).Times(2); // once here and once in CommandMove
	EXPECT_CALL(mcmv, setVelocity).Times(1); //once here

	EXPECT_CALL(mcmv, getPosition).Times(2); // once here and once in CommandMove
	EXPECT_CALL(mcmv, getVelocity).Times(1); // once in CommandMove

	mcmv.setPosition(position);
	mcmv.setVelocity(velocity);

	CommandMove<int> CommandMove(mcmv);
	CommandMove.execute();

	EXPECT_EQ(mcmv.getPosition(), position + velocity);
}

TEST(Tanks_MovableComponent, UseFullMoveCommandSequence)
{
	UObject obj;
	std::vector<int> position = { 10, 20, 30 };
	std::vector<int> velocity = { 45, 25, 55 };

	GameQueueRealization gameQueue;

	MockMovable<int> mcmv;

	EXPECT_CALL(mcmv, setPosition).Times(3); // once here and once in CommandMove on each call of CommandStartMove
	EXPECT_CALL(mcmv, setVelocity).Times(4); // twice on each iteration of CommandStartMove

	EXPECT_CALL(mcmv, getPosition).Times(5); // three times here and once in CommandMove on each call of CommandStartMove
	EXPECT_CALL(mcmv, getVelocity).Times(3); // once here and once in CommandMove on each call of CommandStartMove

	mcmv.setPosition(position);

	CommandStartMove<int> commandStart(obj, gameQueue, mcmv, velocity);
	gameQueue.push(static_cast<ICommand*>(&commandStart));

	CommandEndMove commandEnd(obj);
	gameQueue.push(static_cast<ICommand*>(&commandEnd));

	// Check for correct turning and angle velocity set
	gameQueue.front()->execute(); // StartCommand
	gameQueue.pop();
	EXPECT_TRUE(vectorEachValEq(mcmv.getVelocity(), 0)); // StartCommand sets and cleans velocity on each call
	EXPECT_EQ(mcmv.getPosition(), position + velocity);

	gameQueue.front()->execute(); // EndCommand, StartCommand is going to be run by inertion 1 time
	gameQueue.pop();

	// Check for continuous turning
	const std::vector<int> expectedPosition = mcmv.getPosition() + velocity; //

	gameQueue.front()->execute(); // Intertion CommandStartMove
	gameQueue.pop();

	EXPECT_EQ(mcmv.getPosition(), expectedPosition);

	gameQueue.front()->execute(); // EmptyCommand
	gameQueue.pop();

	EXPECT_EQ(gameQueue.size(), 0);
}
