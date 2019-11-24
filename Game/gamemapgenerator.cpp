#include <iostream>
#include "gamemapgenerator.h"

namespace Game{

GameMapGenerator::GameMapGenerator(std::shared_ptr<GameObjectManager> objManager, std::shared_ptr<GameEventHandler> eventHandler)
{
    objManager_ = objManager;
    eventHandler_ = eventHandler;
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
}

GameMapGenerator::~GameMapGenerator()
{

}
void GameMapGenerator::createBuilding(Course::Coordinate location)
{
    std::shared_ptr<GameTileBase> targetTile = objManager_->getGameTile(location);
    if(targetTile->getType()=="Grassland"){
        std::cout<<"oikea tile"<<std::endl;
        std::shared_ptr<FarmBuilding> newFarm = std::make_shared<FarmBuilding>(eventHandler_,
                                                                               objManager_,
                                                                               objManager_->getPlayer(),
                                                                               1,
                                                                               Game::ConstGameResourceMap::FARM_BUILD_COST,
                                                                               Game::ConstGameResourceMap::FARM_PRODUCTION);
        targetTile->addGameBuilding(newFarm);
        std::cout<<""<<std::endl;
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
                int spriteWidth = x->getSprite()->pixmap().width();
                int spriteHeight = x->getSprite()->pixmap().height();
                x->getSprite()->setPos(j*spriteHeight,i*spriteWidth);
                x->setCoordinate(Course::Coordinate(j*spriteHeight,i*spriteWidth));
                std::cout<<"x: " + std::to_string(j*spriteHeight) + " y: " + std::to_string(i*spriteWidth) + "type: " + x->getType()<<std::endl;
                objManager->addTile(x);
            }
            else if(tileCode == 3){
                std::shared_ptr<Foresttile> x = std::make_shared<Foresttile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite()->pixmap().width();
                int spriteHeight = x->getSprite()->pixmap().height();
                x->getSprite()->setPos(j*spriteHeight,i*spriteWidth);
                x->setCoordinate(Course::Coordinate(j*spriteHeight,i*spriteWidth));
                std::cout<<"x: " + std::to_string(j*spriteHeight) + " y: " + std::to_string(i*spriteWidth) + "type: " + x->getType()<<std::endl;
                objManager->addTile(x);
        }
            else if(tileCode == 1){
                std::shared_ptr<WaterTile> x = std::make_shared<WaterTile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite()->pixmap().width();
                int spriteHeight = x->getSprite()->pixmap().height();
                x->getSprite()->setPos(j*spriteHeight,i*spriteWidth);
                x->setCoordinate(Course::Coordinate(j*spriteHeight,i*spriteWidth));
                std::cout<<"x: " + std::to_string(j*spriteHeight) + " y: " + std::to_string(i*spriteWidth) + "type: " + x->getType()<<std::endl;
                objManager->addTile(x);
        }
    }
    std::shared_ptr<Game::Player> player = std::make_shared<Game::Player>(Course::Coordinate(150,150));
    objManager->setPlayer(player);
}

}
}
