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
    /**
     * @brief Foresttile
     * @param location
     * @param eventhandler
     * @param objectmanager
     * @param max_build
     * @param max_work
     * @param production
     */
    Foresttile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 4,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    /**
     * @brief getType
     * @return type of the tile as a string
     */
    virtual std::string getType() const override;

private:
};
}
#endif // FORESTTILE_H
