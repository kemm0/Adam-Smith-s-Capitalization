#include <iostream>
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
    sprite = QPixmap("../../juho-ja-leo/Game/Sprites/farmhouse.png");
    width = sprite.width();
    height = sprite.height();

}

std::string FarmBuilding::getType() const
{
    return "Farmhouse";

}
}
