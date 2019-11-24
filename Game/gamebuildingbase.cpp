#include "gamebuildingbase.h"

Game::GameBuildingBase::GameBuildingBase(const std::shared_ptr<Game::GameEventHandler> &eventhandler,
                                         const std::shared_ptr<Game::GameObjectManager> &objectmanager,
                                         const std::shared_ptr<Game::Player> &owner,
                                         const int &tilespaces,
                                         const Course::ResourceMap &buildcost,
                                         const Course::ResourceMap &production)
    : Course::BuildingBase(eventhandler,
                           objectmanager,
                           owner,
                           tilespaces,
                           buildcost,
                           production)
{
    sprite = nullptr;
}

QGraphicsPixmapItem *Game::GameBuildingBase::getSprite()
{
    return sprite;
}

int Game::GameBuildingBase::getWidth()
{
    return width;
}

int Game::GameBuildingBase::getHeight()
{
    return height;
}


