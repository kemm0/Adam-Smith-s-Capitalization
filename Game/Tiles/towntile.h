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
    TownTile(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    virtual std::string getType() const override;
    virtual QGraphicsPixmapItem* getSprite() override;
private:
    QGraphicsPixmapItem* sprite;

};
}

#endif // TOWNTILE_H
