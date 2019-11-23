#include "towntile.h"

namespace Game{

TownTile::TownTile(const Course::Coordinate& location,
                     const std::shared_ptr<GameEventHandler>& eventhandler,
                     const std::shared_ptr<GameObjectManager>& objectmanager,
                     const unsigned int& max_build,
                     const unsigned int& max_work,
                     const Course::ResourceMap& production)
    : Game::GameTileBase(location,
                       eventhandler,
                       objectmanager,
                       max_build,
                       max_work,
                       production)
{

    sprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/town.png"));
    //setPixmap(QPixmap("/home/ketotokj/Desktop/Ohjelmointi/Ohjelmointi3/Pirkanmaan_valloitus/juho-ja-leo/Game/Sprites/grasstile2.png"));
}

std::string TownTile::getType() const
{
    return "Town";
}

QGraphicsPixmapItem *TownTile::getSprite()
{
    return sprite;
}
}
