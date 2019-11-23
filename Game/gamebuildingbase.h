#ifndef GAMEBUILDINGBASE_H
#define GAMEBUILDINGBASE_H

#include "../CourseLib/buildings/buildingbase.h"
#include "QGraphicsPixmapItem"
#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gameresourcemap.h"

namespace Game {


class GameBuildingBase : public Course::BuildingBase
{
public:
    GameBuildingBase(const std::shared_ptr<GameEventHandler>& eventhandler,
                     const std::shared_ptr<GameObjectManager>& objectmanager,
                     const std::shared_ptr<Player>& owner,
                     const int& tilespaces = 1,
                     const Course::ResourceMap& buildcost = {},
                     const Course::ResourceMap& production = {});
    virtual QGraphicsPixmapItem* getSprite();
private:
    QGraphicsPixmapItem* sprite;
};
}

#endif // GAMEBUILDINGBASE_H
