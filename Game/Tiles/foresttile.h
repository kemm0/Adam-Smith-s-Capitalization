#ifndef FORESTTILE_H
#define FORESTTILE_H

#include "../CourseLib/tiles/tilebase.h"
#include "QGraphicsPixmapItem"
#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gametilebase.h"
#include "gamebuildingbase.h"

namespace Game{
/**
 * @brief The Foresttile class represents forest
 */
class Foresttile: public Game::GameTileBase//, public QGraphicsPixmapItem
{
public:
    Foresttile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    virtual std::string getType() const override;
    virtual QPixmap getSprite() override;

private:
};
}
#endif // FORESTTILE_H
