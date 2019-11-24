#include "loggingbuilding.h"

namespace Game {


LoggingBuilding::LoggingBuilding(const std::shared_ptr<GameEventHandler>& eventhandler,
           const std::shared_ptr<GameObjectManager>& objectmanager,
           const std::shared_ptr<Game::Player>& owner,
           const int& tilespaces,
           const Course::ResourceMap& buildcost,
           const Course::ResourceMap& production):

    Game::GameBuildingBase(eventhandler,
                         objectmanager,
                         owner,
                         tilespaces,
                         buildcost,
                         production)
{
    sprite = new QGraphicsPixmapItem(QPixmap("../../juho-ja-leo/Game/Sprites/logcabin.png"));
    width = sprite->pixmap().width();
    height = sprite->pixmap().height();


}

std::string LoggingBuilding::getType() const
{
 return "Logging cabin";
}

}
