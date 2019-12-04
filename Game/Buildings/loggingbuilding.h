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
 * @brief The LoggingBuilding class represents a logging cabin
 */
class LoggingBuilding: public Game::GameBuildingBase
{
public:
    /**
     * @brief LoggingBuilding
     * @param eventhandler
     * @param objectmanager
     * @param owner
     * @param tilespaces
     * @param buildcost
     * @param production
     */
    LoggingBuilding(
            const std::shared_ptr<GameEventHandler>& eventhandler,
            const std::shared_ptr<GameObjectManager>& objectmanager,
            const std::shared_ptr<Game::Player>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Game::ConstGameResourceMap::LOGGING_BUILD_COST,
            const Course::ResourceMap& production = Game::ConstGameResourceMap::LOGGING_PRODUCTION);
    /**
     * @brief getType
     * @return
     */
    virtual std::string getType() const override;
};
}
#endif // LOGGINGBUILDING_H
