#include "farmbuilding.h"

namespace Game {


FarmBuilding::FarmBuilding(const std::shared_ptr<GameEventHandler>& eventhandler,
           const std::shared_ptr<GameObjectManager>& objectmanager,
           const std::shared_ptr<Game::Player>& owner,
           const int& tilespaces,
           const Course::ResourceMap& buildcost,
           const Course::ResourceMap& production)

    : Course::BuildingBase(eventhandler,
                           objectmanager,
                           owner,
                           tilespaces,
                           buildcost,
                           production)
{
    sprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/farm.png"));


}
}
