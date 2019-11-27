#include <iostream>
#include "gamemapgenerator.h"

namespace Game{

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
    createMapObjects(objManager_,eventHandler_);
    setRobber();
    setTreasure();
}

GameMapGenerator::~GameMapGenerator()
{

}
void GameMapGenerator::createBuilding(Course::Coordinate location)
{
    std::shared_ptr<GameTileBase> targetTile = objManager_->getGameTile(location);
    if(targetTile->getType()=="Grassland"){
        std::cout<<"Tile type: Grassland"<<std::endl;
        std::shared_ptr<FarmBuilding> newFarm = std::make_shared<FarmBuilding>(eventHandler_,
                                                                               objManager_,
                                                                               objManager_->getPlayer(),
                                                                               1,
                                                                               Game::ConstGameResourceMap::FARM_BUILD_COST,
                                                                               Game::ConstGameResourceMap::FARM_PRODUCTION);


        if (objManager_->getPlayer()->setMoney(newFarm->BUILD_COST)){
            objManager_->getPlayer()->addObject(newFarm);
            std::cout<<"Adding game building"<<std::endl;
            targetTile->addGameBuilding(newFarm);
            std::cout<< std::to_string(objManager_->getPlayer()->getMoney()) << std::endl;
        }
        else{
            std::cout<<"Out of money"<<std::endl;
        }


    }
    else if(targetTile->getType()=="Forest"){
        std::cout<<"Tile type: Grassland"<<std::endl;
        std::shared_ptr<LoggingBuilding> newCabin = std::make_shared<LoggingBuilding>(eventHandler_,
                                                                               objManager_,
                                                                               objManager_->getPlayer(),
                                                                               1,
                                                                               Game::ConstGameResourceMap::LOGGING_BUILD_COST,
                                                                               Game::ConstGameResourceMap::LOGGING_PRODUCTION);

        if (objManager_->getPlayer()->setMoney(newCabin->BUILD_COST)){
            objManager_->getPlayer()->addObject(newCabin);
            std::cout<<"Adding game building"<<std::endl;
            targetTile->addGameBuilding(newCabin);
            std::cout<< std::to_string(objManager_->getPlayer()->getMoney()) << std::endl;
        }
        else{
            std::cout<<"Out of money"<<std::endl;
        }


    }
    else if(targetTile->getType()=="Water"){
        std::cout<<"Tile type: Grassland"<<std::endl;
        std::shared_ptr<FishingBuilding> newFishingHut = std::make_shared<FishingBuilding>(eventHandler_,
                                                                               objManager_,
                                                                               objManager_->getPlayer(),
                                                                               1,
                                                                               Game::ConstGameResourceMap::FISHING_BUILD_COST,
                                                                               Game::ConstGameResourceMap::FISHING_PRODUCTION);
        if (objManager_->getPlayer()->setMoney(newFishingHut->BUILD_COST)){
            objManager_->getPlayer()->addObject(newFishingHut);
            std::cout<<"Adding game building"<<std::endl;
            targetTile->addGameBuilding(newFishingHut);
            std::cout<< std::to_string(objManager_->getPlayer()->getMoney()) << std::endl;
        }
        else{
            std::cout<<"Out of money"<<std::endl;
        }


    }

}

Course::Coordinate GameMapGenerator::getRandomMapCoordinate()
{
    int randX = rand() % mapWidth * 50;
    int randY = rand() % mapHeight * 50;
    std::cout<<"X: " + std::to_string(randX) + " y: " + std::to_string(randX)<<std::endl;
    return Course::Coordinate(randX,randY);
}

void GameMapGenerator::setTreasure()
{
    while(true){
        Course::Coordinate randMapCoordinate = getRandomMapCoordinate();
        std::shared_ptr<GameTileBase> tile = objManager_->getGameTile(randMapCoordinate);
        bool hasRobber = tile->getRobber();
        if(!hasRobber){
            tile->setRobber(true);
            std::cout<<"Tile x: " + std::to_string(tile->getCoordinate().x()) + " y: " + std::to_string(tile->getCoordinate().y()) + " has Treasure"<<std::endl;
            break;
        }
    }
}

void GameMapGenerator::setRobber()
{
    int robberAmount = 3;
    int robbersSet = 0;
    while(robbersSet < robberAmount){
        Course::Coordinate randMapCoordinate = getRandomMapCoordinate();
        std::shared_ptr<GameTileBase> tile = objManager_->getGameTile(randMapCoordinate);
        std::cout<<"a"<<std::endl;
        bool hasTreasure = tile->getTreasure();
        if(!hasTreasure){
            tile->setRobber(true);
            robbersSet += 1;
        }
    }
    for(auto tile: objManager_->getGameTiles()){
        if(tile->getRobber()){
                        std::cout<<"Tile x: " + std::to_string(tile->getCoordinate().x()) + " y: " + std::to_string(tile->getCoordinate().y()) + " has Robber"<<std::endl;
        }
    }
}

void GameMapGenerator::createMapObjects(std::shared_ptr<GameObjectManager> objManager,std::shared_ptr<GameEventHandler> eventHandler)
{
    std::cout<<"Game objects: " <<std::endl;
    for(unsigned int i = 0; i < mapTemplate.size(); i++){
        for(unsigned int j = 0; j < mapTemplate.at(i).size();j++){
            int tileCode = mapTemplate.at(i).at(j);
            if(tileCode == 0){
                std::shared_ptr<GrassTile> x = std::make_shared<GrassTile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite().width();
                int spriteHeight = x->getSprite().height();
                x->setCoordinate(Course::Coordinate(j*spriteHeight,i*spriteWidth));
                std::cout<<"x: " + std::to_string(j*spriteHeight) + " y: " + std::to_string(i*spriteWidth) + "type: " + x->getType()<<std::endl;
                objManager->addGameTile(x);
            }
            else if(tileCode == 3){
                std::shared_ptr<Foresttile> x = std::make_shared<Foresttile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite().width();
                int spriteHeight = x->getSprite().height();
                x->setCoordinate(Course::Coordinate(j*spriteHeight,i*spriteWidth));
                std::cout<<"x: " + std::to_string(j*spriteHeight) + " y: " + std::to_string(i*spriteWidth) + "type: " + x->getType()<<std::endl;
                objManager->addGameTile(x);
        }
            else if(tileCode == 1){
                std::shared_ptr<WaterTile> x = std::make_shared<WaterTile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite().width();
                int spriteHeight = x->getSprite().height();
                x->setCoordinate(Course::Coordinate(j*spriteHeight,i*spriteWidth));
                std::cout<<"x: " + std::to_string(j*spriteHeight) + " y: " + std::to_string(i*spriteWidth) + "type: " + x->getType()<<std::endl;
                objManager->addGameTile(x);
        }
    }
    std::shared_ptr<Game::Player> player = std::make_shared<Game::Player>(Course::Coordinate(150,150));
    objManager->setPlayer(player);
}

}
}
