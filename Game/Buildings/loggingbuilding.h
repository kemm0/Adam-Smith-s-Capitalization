#ifndef LOGGINGBUILDING_H
#define LOGGINGBUILDING_H

#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "../CourseLib/buildings/buildingbase.h"
#include "../CourseLib/core/resourcemaps.h"
#include "gamebuildingbase.h"

namespace Game {
/**
 * @brief The LoggingBuilding class represents logging cabin
 */
class LoggingBuilding: public Game::GameBuildingBase
{
public:
    LoggingBuilding(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<GameObjectManager>& objectmanager,
                const std::shared_ptr<Game::Player>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& buildcost = Game::ConstGameResourceMap::LOGGING_BUILD_COST,
                const Course::ResourceMap& production = Game::ConstGameResourceMap::LOGGING_PRODUCTION);
    virtual std::string getType() const override;
};
}
#endif // LOGGINGBUILDING_H
