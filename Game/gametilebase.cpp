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

bool GameTileBase::getRobber()
{
    return hasRobber;
}

bool GameTileBase::getTreasure()
{
    return hasTreasure;
}

bool GameTileBase::setRobber(bool x)
{
    hasRobber = x;
}

bool GameTileBase::setTreasure(bool x)
{
    hasTreasure = x;
}

void GameTileBase::setSprite(QPixmap image)
{
    sprite = new QGraphicsPixmapItem(image);
}
}
