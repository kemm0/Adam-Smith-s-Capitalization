#include "gameeventhandler.h"
#include "gametilebase.h"
#include "gamebuildingbase.h"
#include "Buildings/farmbuilding.h"


namespace Game{

GameEventHandler::GameEventHandler(std::shared_ptr<GameObjectManager> manager, QObject *parent)
    :QObject(parent)
{
    objManager = manager;
    diceValue = 0;
    srand(time(NULL));
    turn = 1;
    threw = false;
    moved = false;
    moving = false;
    building = false;
    built = false;
    searching = false;
    searchedArea = false;
    hiring = false;
    hired = false;
    selectedBuildingType = "";
    workertype = "novice worker";
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

bool GameEventHandler::getPlayerBuilt()
{
    return built;
}

bool GameEventHandler::getPlayerSearched()
{
    return searchedArea;
}

bool GameEventHandler::isSearching()
{
    return searching;
}

bool GameEventHandler::isHiring()
{
    return hiring;
}

bool GameEventHandler::getHired()
{
    return hired;
}


std::string GameEventHandler::getSelectedBuildingType()
{
    return selectedBuildingType;
}

std::string GameEventHandler::getWorkerType()
{
    return workertype;
}

void GameEventHandler::setThrown(bool x)
{
    threw = x;
}

void GameEventHandler::setPlayerMoved(bool x)
{
    moved = x;
}

void GameEventHandler::setPlayerBuilt(bool x)
{
    built = x;
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

void GameEventHandler::setSearching(bool x)
{
    searching = x;
}

void GameEventHandler::setPlayerSearched(bool x)
{
    searchedArea = x;
}

void GameEventHandler::setPlayerHired(bool x)
{
    hired = x;
}

void GameEventHandler::setHiring(bool x)
{
    hiring = x;
}

void GameEventHandler::setWorkerType(std::string type)
{
    workertype = type;
}


void GameEventHandler::nextTurn()
{
    turn += 1;
}

int GameEventHandler::searchArea(std::vector<std::shared_ptr<Game::GameTileBase> > area)
{

}

void GameEventHandler::checkIfOutOfMoney(std::map<Course::BasicResource, int> amount)
{
    //Amounts integer is negative
    if(amount[Course::MONEY] <=  0 - objManager->getPlayer()->getMoney()){
        emit gameOver(true);
    }

}


}
