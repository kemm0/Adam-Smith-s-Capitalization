#include <iostream>
#include "gamemapgenerator.h"
#include "../CourseLib/exceptions/illegalaction.h"
#include "../CourseLib/exceptions/invalidpointer.h"
#include "../CourseLib/exceptions/notenoughspace.h"

namespace Game{

enum mapCodes{
    GRASSLAND = 0,
    WATER = 1,
    FOREST = 3,
};

GameMapGenerator::GameMapGenerator(std::shared_ptr<GameObjectManager> objManager, std::shared_ptr<GameEventHandler> eventHandler)
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
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
    /*for(int i = 0; i< 100; i++){
        getRandomMapCoordinate();
    }*/
    createMapObjects();
    setRobber(100);
    setTreasure(100);
}

GameMapGenerator::~GameMapGenerator()
{

}
void GameMapGenerator::createBuilding(Course::Coordinate location)
{
    std::shared_ptr<GameTileBase> targetTile = objManager_->getGameTile(location);
    if(targetTile->getType()=="Grassland"){
        createFarmhouse(targetTile);

    }
    else if(targetTile->getType()=="Forest"){
        createLoggingcabin(targetTile);


    }
    else if(targetTile->getType()=="Water"){
        createFishinghut(targetTile);
    }

}

Course::Coordinate GameMapGenerator::getRandomMapCoordinate()
{
    int randX = rand() % mapWidth * 50;
    int randY = rand() % mapHeight * 50;
    //std::cout<<"X: " + std::to_string(randX) + " y: " + std::to_string(randX)<<std::endl;
    return Course::Coordinate(randX,randY);
}

void GameMapGenerator::setTreasure(int amount)
{
    int treasuresSet = 0;
    while(treasuresSet < amount){
        Course::Coordinate randMapCoordinate = getRandomMapCoordinate();
        std::shared_ptr<GameTileBase> tile = objManager_->getGameTile(randMapCoordinate);
        bool hasRobber = tile->getRobber();
        if(!hasRobber){
            tile->setTreasure(true);
            treasuresSet += 1;
        }
    }
    for(auto tile: objManager_->getGameTiles()){
        if(tile->getTreasure()==true){
            //std::cout<<"Tile x: " + std::to_string(tile->getCoordinate().x()) + " y: " + std::to_string(tile->getCoordinate().y()) + " has treasure"<<std::endl;
        }
    }
}

void GameMapGenerator::setRobber(int amount)
{
    int robbersSet = 0;
    while(robbersSet < amount){
        Course::Coordinate randMapCoordinate = getRandomMapCoordinate();
        std::shared_ptr<GameTileBase> tile = objManager_->getGameTile(randMapCoordinate);
        bool hasTreasure = tile->getTreasure();
        if(!hasTreasure){
            tile->setRobber(true);
            robbersSet += 1;
        }
    }
    for(auto tile: objManager_->getGameTiles()){
        if(tile->getRobber()){
                        //std::cout<<"Tile x: " + std::to_string(tile->getCoordinate().x()) + " y: " + std::to_string(tile->getCoordinate().y()) + " has Robber"<<std::endl;
        }
    }
}

void GameMapGenerator::createGrassTile(Course::Coordinate location)
{
    int x = location.x();
    int y = location.y();
    std::shared_ptr<GrassTile> newTile = std::make_shared<GrassTile>(location,eventHandler_,objManager_);
    int spriteWidth = newTile->getSprite().width();
    int spriteHeight = newTile->getSprite().height();
    newTile->setCoordinate(Course::Coordinate(x*spriteHeight,y*spriteWidth));
    //std::cout<<"x: " + std::to_string(x*spriteHeight) + " y: " + std::to_string(x*spriteWidth) + "type: " + newTile->getType()<<std::endl;
    objManager_->addGameTile(newTile);
}

void GameMapGenerator::createForestTile(Course::Coordinate location)
{
    int x = location.x();
    int y = location.y();
    std::shared_ptr<Foresttile> newTile = std::make_shared<Foresttile>(location,eventHandler_,objManager_);
    int spriteWidth = newTile->getSprite().width();
    int spriteHeight = newTile->getSprite().height();
    newTile->setCoordinate(Course::Coordinate(x*spriteHeight,y*spriteWidth));
    //std::cout<<"x: " + std::to_string(x*spriteHeight) + " y: " + std::to_string(x*spriteWidth) + "type: " + newTile->getType()<<std::endl;
    objManager_->addGameTile(newTile);
}

void GameMapGenerator::createWaterTile(Course::Coordinate location)
{
    int x = location.x();
    int y = location.y();
    std::shared_ptr<WaterTile> newTile = std::make_shared<WaterTile>(location,eventHandler_,objManager_);
    int spriteWidth = newTile->getSprite().width();
    int spriteHeight = newTile->getSprite().height();
    newTile->setCoordinate(Course::Coordinate(x*spriteHeight,y*spriteWidth));
    //std::cout<<"x: " + std::to_string(x*spriteHeight) + " y: " + std::to_string(x*spriteWidth) + "type: " + newTile->getType()<<std::endl;
    objManager_->addGameTile(newTile);

}

void GameMapGenerator::createPlayer(Course::Coordinate location)
{
    std::shared_ptr<Game::Player> player = std::make_shared<Game::Player>(location);
    objManager_->setPlayer(player);
}

void GameMapGenerator::createWorker(std::shared_ptr<GameTileBase> targetTile)
{
    if(eventHandler_->getWorkerType() == "novice worker" && targetTile->hasSpaceForWorkers(1)){
        std::cout<<"creating novice worker"<<std::endl;
        std::shared_ptr<NoviceWorker> worker = std::make_shared<NoviceWorker>(eventHandler_,
                                                                                 objManager_,
                                                                                 objManager_->getPlayer(),
                                                                                 1,
                                                                                 Game::ConstGameResourceMap::NW_RECRUITMENT_COST,
                                                                                 Game::ConstGameResourceMap::NW_WORKER_EFFICIENCY
                                                                                 );
        std::cout<<"worker created"<<std::endl;
        try {
            targetTile->addWorker(worker);

        } catch (Course::IllegalAction) {
            std::cout<<"illegalaction"<<std::endl;
        }
        catch(Course::InvalidPointer){
            std::cout<<"invalidptr"<<std::endl;
        }
        catch(Course::NotEnoughSpace){
            std::cout<<"no space"<<std::endl;
        }

        objManager_->workers.push_back(worker);
        std::cout<<targetTile->getWorkerCount()<<std::endl;
        std::cout<<targetTile->hasSpaceForWorkers(1)<<std::endl;
    }
    else if(eventHandler_->getWorkerType() == "apprentice worker"){
        std::shared_ptr<ApprenticeWorker> worker = std::make_shared<ApprenticeWorker>(eventHandler_,
                                                                                 objManager_,
                                                                                 objManager_->getPlayer(),
                                                                                 1,
                                                                                 Game::ConstGameResourceMap::AW_RECRUITMENT_COST,
                                                                                 Game::ConstGameResourceMap::AW_WORKER_EFFICIENCY
                                                                                 );
        targetTile->addWorker(worker);
    }
    else if(eventHandler_->getWorkerType() == "master worker"){
        std::shared_ptr<MasterWorker> worker = std::make_shared<MasterWorker>(eventHandler_,
                                                                                 objManager_,
                                                                                 objManager_->getPlayer(),
                                                                                 1,
                                                                                 Game::ConstGameResourceMap::MW_RECRUITMENT_COST,
                                                                                 Game::ConstGameResourceMap::MW_WORKER_EFFICIENCY
                                                                                 );
        targetTile->addWorker(worker);
    }
}

void GameMapGenerator::createFarmhouse(std::shared_ptr<GameTileBase> targetTile)
{
    std::shared_ptr<FarmBuilding> newFarm = std::make_shared<FarmBuilding>(eventHandler_,
                                                                           objManager_,
                                                                           objManager_->getPlayer(),
                                                                           1,
                                                                           Game::ConstGameResourceMap::FARM_BUILD_COST,
                                                                           Game::ConstGameResourceMap::FARM_PRODUCTION);


    objManager_->getPlayer()->setMoney(newFarm->BUILD_COST);
    objManager_->getPlayer()->addObject(targetTile);
    targetTile->addGameBuilding(newFarm);
}

void GameMapGenerator::createLoggingcabin(std::shared_ptr<GameTileBase> targetTile)
{
    std::shared_ptr<LoggingBuilding> newCabin = std::make_shared<LoggingBuilding>(eventHandler_,
                                                                           objManager_,
                                                                           objManager_->getPlayer(),
                                                                           1,
                                                                           Game::ConstGameResourceMap::LOGGING_BUILD_COST,
                                                                           Game::ConstGameResourceMap::LOGGING_PRODUCTION);

    objManager_->getPlayer()->setMoney(newCabin->BUILD_COST);
    objManager_->getPlayer()->addObject(targetTile);
    targetTile->addGameBuilding(newCabin);
}

void GameMapGenerator::createFishinghut(std::shared_ptr<GameTileBase> targetTile)
{
    std::shared_ptr<FishingBuilding> newFishingHut = std::make_shared<FishingBuilding>(eventHandler_,
                                                                           objManager_,
                                                                           objManager_->getPlayer(),
                                                                           1,
                                                                           Game::ConstGameResourceMap::FISHING_BUILD_COST,
                                                                           Game::ConstGameResourceMap::FISHING_PRODUCTION);
    objManager_->getPlayer()->setMoney(newFishingHut->BUILD_COST);
    objManager_->getPlayer()->addObject(targetTile);
    targetTile->addGameBuilding(newFishingHut);
}

void GameMapGenerator::createMapObjects()
{
    for(unsigned int i = 0; i < mapTemplate.size(); i++){
        for(unsigned int j = 0; j < mapTemplate.at(i).size();j++){
            int tileCode = mapTemplate.at(i).at(j);
            if(tileCode == GRASSLAND){
                createGrassTile(Course::Coordinate(j,i));
            }
            else if(tileCode == FOREST){
                createForestTile(Course::Coordinate(j,i));
        }
            else if(tileCode == WATER){
                createWaterTile(Course::Coordinate(j,i));
        }
    }
    createPlayer(getRandomMapCoordinate());
}

}
}
