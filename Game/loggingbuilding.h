#ifndef LOGGINGBUILDING_H
#define LOGGINGBUILDING_H

#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "../CourseLib/buildings/buildingbase.h"
#include "../CourseLib/core/resourcemaps.h"

namespace Game {


class LoggingBuilding: public Course::BuildingBase
{
public:
    LoggingBuilding(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<GameObjectManager>& objectmanager,
                const std::shared_ptr<Game::Player>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& buildcost = Course::ConstResourceMaps::FARM_BUILD_COST,
                const Course::ResourceMap& production = Course::ConstResourceMaps::FARM_PRODUCTION);
    QGraphicsPixmapItem* sprite;
};
}
#endif // LOGGINGBUILDING_H
