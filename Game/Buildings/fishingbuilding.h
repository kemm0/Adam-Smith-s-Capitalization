#ifndef FISHINGBUILDING_H
#define FISHINGBUILDING_H

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
 * @brief The FishingBuilding class represents a fishing hut
 */
class FishingBuilding: public Game::GameBuildingBase
{
public:
    /**
     * @brief FishingBuilding
     * @param eventhandler
     * @param objectmanager
     * @param owner
     * @param tilespaces
     * @param buildcost
     * @param production
     */
    FishingBuilding(
            const std::shared_ptr<GameEventHandler>& eventhandler,
            const std::shared_ptr<GameObjectManager>& objectmanager,
            const std::shared_ptr<Game::Player>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Game::ConstGameResourceMap::FISHING_BUILD_COST,
            const Course::ResourceMap& production = Game::ConstGameResourceMap::FISHING_PRODUCTION);
    /**
     * @brief getType
     * @return type of the building as a string
     */
    virtual std::string getType() const override;
};
}
#endif // FISHINGBUILDING_H
