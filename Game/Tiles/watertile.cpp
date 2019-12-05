#include "watertile.h"

namespace Game{

WaterTile::WaterTile(
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
    sprite = QPixmap("../../juho-ja-leo/Game/Sprites/water.png");
    width = sprite.width();
    height = sprite.height();
    setDescription("brief","This is a body of water.\nMurky, but it is full "
                           "of fish.\nLooks like a good place for fishing.");
}

std::string WaterTile::getType() const
{
    return "Water";
}

}

