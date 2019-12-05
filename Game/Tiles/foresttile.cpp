#include "foresttile.h"

namespace Game{

Foresttile::Foresttile(
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

    sprite = QPixmap("../../juho-ja-leo/Game/Sprites/forest.png");
    width = sprite.width();
    height = sprite.height();
    setDescription("brief","This is a typical finnish forest.\nLooks like a "
                           "good place for logging");
}

std::string Foresttile::getType() const
{
    return "Forest";
}

}
