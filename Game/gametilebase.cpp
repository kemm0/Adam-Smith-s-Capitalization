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
    sprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/water.png"));
}

QGraphicsPixmapItem *GameTileBase::getSprite()
{

}

void GameTileBase::setSprite()
{

}

std::string GameTileBase::getType() const
{

}
}
