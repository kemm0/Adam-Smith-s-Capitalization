#ifndef GAMETILEBASE_H
#define GAMETILEBASE_H

#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gameresourcemap.h"
#include "gamebuildingbase.h"

namespace Game{

class GameTileBase : public Course::TileBase
{
public:
    GameTileBase(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    virtual QPixmap getSprite();
    /**
     * @brief Adds a new Building-object to the tile.
     *
     * Phases: \n
     * 1. Tile checks if it has space for the building. \n
     * 2. Building checks whether it can be placed on this tile. \n
     * 3. Building is added to this Tile. \n
     * 4. Tile update's Building's location. \n
     *
     * @param building A pointer to the Building that is being added.
     * @post Exception guarantee: Basic
     * @exception InvalidPointer - If the building's pointer doesn't
     * point to anything or ObjectManager doesn't return valid shared_ptr to
     * this tile.
     * @exception IllegalMove - Any IllegalException can be thrown by a Tile
     * or Building if it breaks a placement rule.
     * @exception NotEnoughSpace (IllegalMove) - If the tile doesn't have enough
     * space for the Building.
     */
    virtual void addGameBuilding(const std::shared_ptr<Game::GameBuildingBase>& building);
    bool getRobber();
    bool getTreasure();
    int getHeight();
    int getWidth();
    std::vector<std::shared_ptr<GameBuildingBase>> buildingsOnTile;

    bool setRobber(bool x);
    bool setTreasure(bool x);
protected:
    QPixmap sprite;
    bool hasRobber;
    bool hasTreasure;
    int treasure;
    int width;
    int height;
    std::vector<std::shared_ptr<Course::WorkerBase>> workers;
};
}
#endif // GAMETILEBASE_H
