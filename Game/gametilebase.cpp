#include <iostream>
#include "gametilebase.h"
namespace Game{

GameTileBase::GameTileBase(const Course::Coordinate &location,
                                 const std::shared_ptr<Game::GameEventHandler> &eventhandler,
                                 const std::shared_ptr<Game::GameObjectManager> &objectmanager,
                                 const unsigned int &max_build, const unsigned int &max_work,
                                 const Course::ResourceMap &production)
    : Course::TileBase(location,
                       eventhandler,
                       objectmanager,
                       max_build,
                       max_work,
                       production)
{
    sprite = nullptr;
    hasTreasure = false;
    hasRobber = false;
}

QGraphicsPixmapItem *GameTileBase::getSprite()
{
    return sprite;
}

void GameTileBase::addGameBuilding(const std::shared_ptr<GameBuildingBase> &building)
{
    buildingsOnTile.push_back(building);
    std::cout<<"size of buildings on this tile after adding: " + std::to_string(buildingsOnTile.size())<<std::endl;
    sprite = building->getSprite();
    //QPixmap pm = building->getSprite()->pixmap();
    //sprite->setPixmap(pm);
    //std::cout<<"tried to modify sprite"<<std::endl;
}


bool GameTileBase::getRobber()
{
    return hasRobber;
}

bool GameTileBase::getTreasure()
{
    return hasTreasure;
}

int GameTileBase::getHeight()
{
    return height;
}

int GameTileBase::getWidth()
{
    return width;
}


bool GameTileBase::setRobber(bool x)
{
    hasRobber = x;
}

bool GameTileBase::setTreasure(bool x)
{
    hasTreasure = x;
}

}
