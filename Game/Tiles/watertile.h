#ifndef WATERTILE_H
#define WATERTILE_H

#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gametilebase.h"

namespace Game{
/**
 * @brief The WaterTile class represents water
 */
class WaterTile: public Game::GameTileBase//, public QGraphicsPixmapItem
{
public:
    /**
     * @brief WaterTile
     * @param location
     * @param eventhandler
     * @param objectmanager
     * @param max_build
     * @param max_work
     * @param production
     */
    WaterTile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 5,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    /**
     * @brief getType
     * @return type of the tile as a string
     */
    virtual std::string getType() const override;
private:
};
}


#endif // WATERTILE_H
