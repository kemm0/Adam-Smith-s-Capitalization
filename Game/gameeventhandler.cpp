#include "gameeventhandler.h"

namespace Game{

GameEventHandler::GameEventHandler()
{
    diceValue = 0;
    srand(time(NULL));
    turn = 1;
    threw = false;
}

GameEventHandler::~GameEventHandler()
{

}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{

}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{

}

void GameEventHandler::endTurn()
{
    turn += 1;
    threw = false;
}

int GameEventHandler::throwDice()
{
    diceValue = rand() % 6 + 1;
    threw = true;
    return diceValue;
}

int GameEventHandler::getDiceValue()
{
    return diceValue;
}

int GameEventHandler::getTurn()
{
    return turn;
}
}
