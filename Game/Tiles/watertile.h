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
    WaterTile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    virtual std::string getType() const override;
private:
};
}


#endif // WATERTILE_H
