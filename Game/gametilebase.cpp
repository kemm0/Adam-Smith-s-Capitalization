#include <iostream>
#include "gametilebase.h"
namespace Game{

GameTileBase::GameTileBase(
        const Course::Coordinate &location,
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
    sprite = QPixmap(50,50);
    hasTreasure = false;
    hasRobber = false;
}

QPixmap GameTileBase::getSprite()
{
    return sprite;
}

void GameTileBase::updateSprite(QPixmap newSprite)
{
    sprite = newSprite;
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

bool GameTileBase::setRobber(bool robber)
{
    hasRobber = robber;
}

bool GameTileBase::setTreasure(bool treasure)
{
    hasTreasure = treasure;
}

}
