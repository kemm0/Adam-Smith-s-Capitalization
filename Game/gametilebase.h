#ifndef GAMETILEBASE_H
#define GAMETILEBASE_H

#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gameresourcemap.h"

namespace Game{

class GameTileBase : public Course::TileBase
{
public:
    GameTileBase(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    virtual QGraphicsPixmapItem* getSprite();
    bool getRobber();
    bool getTreasure();
    int getHeight();
    int getWidth();

    bool setRobber(bool x);
    bool setTreasure(bool x);
protected:
    QGraphicsPixmapItem* sprite;
    bool hasRobber;
    bool hasTreasure;
    int treasure;
    int width;
    int height;
};
}
#endif // GAMETILEBASE_H
