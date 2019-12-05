#include "towntile.h"

namespace Game{

TownTile::TownTile(
         const Course::Coordinate& location,
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

    sprite = QPixmap("../../juho-ja-leo/Game/Sprites/town.png");
    width = sprite.width();
    height = sprite.height();
    setDescription("brief","This is a Finnish town.\nI need to get back there"
                           " to make it to my ride home.\nBut first i need "
                           "to make some money.");
}

std::string TownTile::getType() const
{
    return "Town";
}

}

