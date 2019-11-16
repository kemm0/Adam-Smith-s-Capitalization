#ifndef TOWNTILE_H
#define TOWNTILE_H

#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"

namespace Game{

class TownTile : public Course::TileBase//, public QGraphicsPixmapItem
{
public:
    TownTile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Course::ConstResourceMaps::GRASSLAND_BP);
    QGraphicsPixmapItem* sprite;
private:

};
}

#endif // TOWNTILE_H
