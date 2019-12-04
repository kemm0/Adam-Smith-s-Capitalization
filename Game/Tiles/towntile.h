#ifndef TOWNTILE_H
#define TOWNTILE_H

#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
//#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gametilebase.h"

namespace Game{

class TownTile : public Game::GameTileBase//, public QGraphicsPixmapItem
{
public:
    /**
     * @brief TownTile
     * @param location
     * @param eventhandler
     * @param objectmanager
     * @param max_build
     * @param max_work
     * @param production
     */
    TownTile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 0,
              const unsigned int& max_work = 0,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::EMPTY);
    /**
     * @brief getType
     * @return type of the tile as a string
     */
    virtual std::string getType() const override;
private:

};
}

#endif // TOWNTILE_H
