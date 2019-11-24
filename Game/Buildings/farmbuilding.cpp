#include "farmbuilding.h"

namespace Game {


FarmBuilding::FarmBuilding(const std::shared_ptr<GameEventHandler>& eventhandler,
           const std::shared_ptr<GameObjectManager>& objectmanager,
           const std::shared_ptr<Game::Player>& owner,
           const int& tilespaces,
           const Course::ResourceMap& buildcost,
           const Course::ResourceMap& production)

    : Game::GameBuildingBase(eventhandler,
                           objectmanager,
                           owner,
                           tilespaces,
                           buildcost,
                           production)
{
    sprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/farmhouse.png"));
    width = sprite->pixmap().width();
    height = sprite->pixmap().height();

}

std::string FarmBuilding::getType() const
{
    return "Farmhouse";

}
}
