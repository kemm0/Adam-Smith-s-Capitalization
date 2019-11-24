#ifndef FARMBUILDING_H
#define FARMBUILDING_H

#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "../CourseLib/buildings/buildingbase.h"
#include "../CourseLib/core/resourcemaps.h"
#include "gamebuildingbase.h"


namespace Game {



class FarmBuilding: public Game::GameBuildingBase
{
public:
    FarmBuilding(const std::shared_ptr<GameEventHandler>& eventhandler,
                const std::shared_ptr<GameObjectManager>& objectmanager,
                const std::shared_ptr<Game::Player>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& buildcost = Game::ConstGameResourceMap::FARM_BUILD_COST,
                const Course::ResourceMap& production = Game::ConstGameResourceMap::FARM_PRODUCTION);
    QGraphicsPixmapItem* sprite;
    virtual std::string getType() const override;
};
}

#endif // FARMBUILDING_H
