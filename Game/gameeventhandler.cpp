#include "gameeventhandler.h"
#include "gametilebase.h"
#include "gamebuildingbase.h"
namespace Game{

GameEventHandler::GameEventHandler()
{
    diceValue = 0;
    srand(time(NULL));
    turn = 1;
    threw = false;
    moved = false;
    moving = false;
    building = false;
    built = false;
    selectedBuildingType = "";
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
    moved = false;
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

bool GameEventHandler::getThrown()
{
    return threw;
}

bool GameEventHandler::getPlayerMoved()
{
    return moved;
}

bool GameEventHandler::isMoving()
{
    return moving;
}

bool GameEventHandler::isBuilding()
{
    return building;
}

std::string GameEventHandler::getSelectedBuildingType()
{
    return selectedBuildingType;
}

void GameEventHandler::setThrown(bool x)
{
    threw = x;
}

void GameEventHandler::setPlayerMoved(bool x)
{
    moved = x;
}

void GameEventHandler::setMoving(bool x)
{
    moving = x;
}

void GameEventHandler::setBuildingState(bool x)
{
    building = x;
}

void GameEventHandler::setSelectedBuildingType(std::string buildingType)
{
    selectedBuildingType =buildingType;
}

void GameEventHandler::nextTurn()
{
    turn += 1;
}

int GameEventHandler::searchArea(std::vector<std::shared_ptr<Game::GameTileBase> > area)
{

}

void GameEventHandler::createBuilding(Course::Coordinate location)
{

}


}
