#include "gamemapgenerator.h"

namespace Game{

GameMapGenerator::GameMapGenerator(std::shared_ptr<GameObjectManager> objManager, std::shared_ptr<GameEventHandler> eventHandler)
{
    objManager_ = objManager;
    eventHandler_ = eventHandler;
    mapTemplate = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0},
        {3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,0,0,0,0,0},
        {3,3,3,3,3,3,3,0,0,0,0,3,3,3,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
        std::shared_ptr<FarmBuilding> newFarm = std::make_shared<FarmBuilding>(eventHandler_,
                                                                               objManager_,
                                                                               objManager_->getPlayer(),
                                                                               1,
                                                                               Game::ConstGameResourceMap::FARM_BUILD_COST,
                                                                               Game::ConstGameResourceMap::FARM_PRODUCTION);
        targetTile->addGameBuilding(newFarm);
    }
}

void GameMapGenerator::createMapObjects(std::shared_ptr<GameObjectManager> objManager,std::shared_ptr<GameEventHandler> eventHandler)
{

    for(unsigned int i = 0; i < mapTemplate.size(); i++){
        for(unsigned int j = 0; j < mapTemplate.at(i).size();j++){
            int tileCode = mapTemplate.at(j).at(i);
            if(tileCode == 0){
                std::shared_ptr<GrassTile> x = std::make_shared<GrassTile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite()->pixmap().width();
                int spriteHeight = x->getSprite()->pixmap().height();
                x->getSprite()->setPos(i*spriteHeight,j*spriteWidth);
                x->setCoordinate(Course::Coordinate(i*spriteHeight,j*spriteWidth));
                objManager->addTile(x);
            }
            else if(tileCode == 3){
                std::shared_ptr<Foresttile> x = std::make_shared<Foresttile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite()->pixmap().width();
                int spriteHeight = x->getSprite()->pixmap().height();
                x->getSprite()->setPos(i*spriteHeight,j*spriteWidth);
                x->setCoordinate(Course::Coordinate(i*spriteHeight,j*spriteWidth));
                objManager->addTile(x);
        }
            else if(tileCode == 1){
                std::shared_ptr<WaterTile> x = std::make_shared<WaterTile>(Course::Coordinate(j,i),eventHandler,objManager);
                int spriteWidth = x->getSprite()->pixmap().width();
                int spriteHeight = x->getSprite()->pixmap().height();
                x->getSprite()->setPos(i*spriteHeight,j*spriteWidth);
                x->setCoordinate(Course::Coordinate(i*spriteHeight,j*spriteWidth));
                objManager->addTile(x);
        }
    }
    std::shared_ptr<Game::Player> player = std::make_shared<Game::Player>(Course::Coordinate(150,150));
    objManager->setPlayer(player);
}

}
}
