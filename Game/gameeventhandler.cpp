#include "gameeventhandler.h"
#include "gametilebase.h"
#include "gamebuildingbase.h"
#include "Buildings/farmbuilding.h"


namespace Game{

GameEventHandler::GameEventHandler(
        std::shared_ptr<GameObjectManager> manager,
        QObject *parent)
    :QObject(parent)
{
    objManager = manager;
    diceValue = 0;
    srand(time(NULL));
    maxTurns = 20;
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
    workertype = "novice worker";
}

GameEventHandler::~GameEventHandler()
{

}

bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource, int amount)
{
    std::shared_ptr<Game::Player> gameplayer = std::dynamic_pointer_cast<
            Game::Player>(player);
    if(gameplayer){
        Course::ResourceMap resources = {{resource,amount}};
        gameplayer->modifyResources(resources);
        return true;
    }
    else{
        return false;
    }
}

bool GameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    std::shared_ptr<Game::Player> gameplayer = std::dynamic_pointer_cast<
            Game::Player>(player);
    if(gameplayer){
        if(resources == ConstGameResourceMap::TREASURE){
            objManager->getPlayer()->setTreasure(true);
        }
        gameplayer->modifyResources(resources);
        int money = gameplayer->getResources().at(Course::MONEY);
        if(money <= 0){
            emit gameOver(BANKRUPT);
        }
        return true;
    }
    else{
        return false;
    }
}




void GameEventHandler::endTurn()
{
    turn += 1;
    if(objManager->getPlayer() != nullptr){
        objManager->getPlayer()->getProfit();
        if(turn == maxTurns){
            //check if player is in a town tile
            bool playerInTown = false;
            for(auto tile: objManager->getGameTiles()){
                if(tile->getType() == "Town"){
                    if(tile->getCoordinate()
                            == objManager->getPlayer()->getCoordinate()){
                        playerInTown = true;
                    }
                }
            }
            if(playerInTown){
                bool foundTreasure = objManager->getPlayer()->hasTreasure();
                bool madeProfit = (objManager->getPlayer()->getResources().at(Course::MONEY)
                        > ConstGameResourceMap::PLAYER_STARTING_RESOURCES.at(Course::MONEY));
                if(!foundTreasure){
                    emit gameOver(NO_TREASURE);
                }
                else if(madeProfit){
                    emit gameOver(GOT_RICH);
                }
                else{
                    emit gameOver(NO_PROFIT);
                }

            }
            else{
                emit gameOver(LATE);
            }
        }
    }
    emit gameMessage("Turn "+ std::to_string(turn) + "\nTurns left: "
                    + std::to_string(maxTurns - turn));
    threw = false;
    moved = false;
    moving = false;
    building = false;
    built = false;
    searching = false;
    searchedArea = false;
    hiring = false;
    hired = false;
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
}
