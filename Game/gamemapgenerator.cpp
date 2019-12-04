#include <iostream>
#include "gamemapgenerator.h"
#include "../CourseLib/exceptions/illegalaction.h"
#include "../CourseLib/exceptions/invalidpointer.h"
#include "../CourseLib/exceptions/notenoughspace.h"

namespace Game{

GameMapGenerator::GameMapGenerator(
        std::shared_ptr<GameObjectManager> objManager,
        std::shared_ptr<GameEventHandler> eventHandler,
        QObject *parent)
    :QObject(parent)
{
    objManager_ = objManager;
    eventHandler_ = eventHandler;
    srand(time(NULL));
    mapTemplate = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0}, // -------> j = x
        {3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,0,0,0,0,0}, // |
        {3,3,3,3,3,3,3,0,0,0,0,3,3,3,0,0,0,0,0,0}, // |
        {0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0}, // |
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // i = y
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,0},
        {1,1,1,1,3,3,3,1,1,1,1,1,1,1,3,3,3,3,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
        {0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,3,3,3},
        {3,3,0,3,3,3,3,3,0,0,3,3,3,0,0,0,0,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3},
    };
    mapWidth = mapTemplate.at(0).size();
    mapHeight = mapTemplate.size();
    createMapObjects();
    setRobber(100);
    setTreasure(100);
}

GameMapGenerator::~GameMapGenerator()
{

}
void GameMapGenerator::createBuilding(Course::Coordinate location)
{
    std::shared_ptr<GameTileBase> targetTile = objManager_->getGameTile(
                location);
    if(targetTile->getType() == "Town"){
        emit gameMessage("You cannot build here."
                         " Find a free area to build on");
        throw Course::IllegalAction();
    }
    else{
        std::shared_ptr<GameBuildingBase> newBuilding;
        if(targetTile->getType()=="Grassland"){
            newBuilding = std::make_shared<FarmBuilding>(
                        eventHandler_,
                        objManager_,
                        objManager_->getPlayer());
        }
        else if(targetTile->getType()=="Forest"){
            newBuilding = std::make_shared<LoggingBuilding>(
                        eventHandler_,
                        objManager_,
                        objManager_->getPlayer());


        }
        else if(targetTile->getType()=="Water"){
            newBuilding = std::make_shared<FishingBuilding>(
                        eventHandler_,
                        objManager_,
                        objManager_->getPlayer());
        }
        eventHandler_->modifyResources(objManager_->getPlayer(),newBuilding->BUILD_COST);
        objManager_->getPlayer()->addObject(targetTile);
        objManager_->addGameObject(newBuilding);
        targetTile->addBuilding(newBuilding);
        targetTile->updateSprite(newBuilding->getSprite());
        emit gameMessage("You built a " + newBuilding->getType() + ".");
    }

}

Course::Coordinate GameMapGenerator::getRandomMapCoordinate()
{
    int randX = rand() % mapWidth * 50;
    int randY = rand() % mapHeight * 50;
    return Course::Coordinate(randX,randY);
}

void GameMapGenerator::setTreasure(int amount)
{
    int treasuresSet = 0;
    while(treasuresSet < amount){
        Course::Coordinate randMapCoordinate = getRandomMapCoordinate();
        std::shared_ptr<GameTileBase> tile = objManager_->getGameTile(
                    randMapCoordinate);
        bool hasRobber = tile->getRobber();
        if(!hasRobber){
            tile->setTreasure(true);
            treasuresSet += 1;
        }
    }
}

void GameMapGenerator::setRobber(int amount)
{
    int robbersSet = 0;
    while(robbersSet < amount){
        Course::Coordinate randMapCoordinate = getRandomMapCoordinate();
        std::shared_ptr<GameTileBase> tile = objManager_->getGameTile(
                    randMapCoordinate);
        bool hasTreasure = tile->getTreasure();
        if(!hasTreasure){
            tile->setRobber(true);
            robbersSet += 1;
        }
    }
}

void GameMapGenerator::createPlayer(Course::Coordinate location)
{
    std::shared_ptr<Game::Player> player = std::make_shared<Game::Player>(
                location);
    objManager_->setPlayer(player);
}

void GameMapGenerator::createWorker(std::shared_ptr<GameTileBase> targetTile)
{
    bool tileHasABuilding = (targetTile->getBuildingCount() != 0);
    if(tileHasABuilding){
        std::shared_ptr<Course::WorkerBase> worker;
        if(eventHandler_->getWorkerType() == "novice worker"){
            worker = std::make_shared<NoviceWorker>(
                eventHandler_,
                objManager_,
                objManager_->getPlayer()
            );
        }
        else if(eventHandler_->getWorkerType() == "apprentice worker"){
            worker = std::make_shared<ApprenticeWorker>(
                eventHandler_,
                objManager_,
                objManager_->getPlayer()
            );
        }
        else if(eventHandler_->getWorkerType() == "master worker"){
            worker = std::make_shared<MasterWorker>(
                eventHandler_,
                objManager_,
                objManager_->getPlayer()
            );

        }
        try {
            targetTile->setOwner(objManager_->getPlayer());
            targetTile->addWorker(worker);
            objManager_->addWorker(worker);
            eventHandler_->modifyResources(
                        objManager_->getPlayer(),
                        worker->RECRUITMENT_COST);
            emit gameMessage("You hired a " + worker->getType() + ".");
        } catch (Course::IllegalAction) {
            emit gameMessage("Cannot place worker."
                             " Tile's worker capacity is full.");
        }
    }
    else{
        emit gameMessage("Tile doesn't have buildings. "
                         "You need a building to accommodate the workers");
    }
}

void GameMapGenerator::createMapObjects()
{
    for(unsigned int i = 0; i < mapTemplate.size(); i++){
        for(unsigned int j = 0; j < mapTemplate.at(i).size();j++){
            int tileCode = mapTemplate.at(i).at(j);
            Course::Coordinate location(j,i);
            std::shared_ptr<Game::GameTileBase> newTile;
            if(tileCode == GRASSLAND){
                newTile = std::make_shared<GrassTile>(
                            location,
                            eventHandler_,
                            objManager_);
            }
            else if(tileCode == FOREST){
                newTile = std::make_shared<Foresttile>(
                            location,
                            eventHandler_,
                            objManager_);
        }
            else if(tileCode == WATER){
                newTile = std::make_shared<WaterTile>(
                            location,
                            eventHandler_,
                            objManager_);

        }
            else if(tileCode == TOWN){
                newTile = std::make_shared<TownTile>(
                            location,
                            eventHandler_,
                            objManager_);

        }
            int spriteWidth = newTile->getSprite().width();
            int spriteHeight = newTile->getSprite().height();
            newTile->setCoordinate(Course::Coordinate(j*spriteHeight,i*spriteWidth));
            objManager_->addGameTile(newTile);
    }
    createPlayer(getRandomMapCoordinate());
}

}
}
