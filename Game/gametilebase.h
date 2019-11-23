#ifndef GAMETILEBASE_H
#define GAMETILEBASE_H

#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/tiles/grassland.h"
#include "QGraphicsPixmapItem"
#include "../CourseLib/core/coordinate.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
namespace Game{

class GameTileBase : public Course::TileBase
{
public:
    GameTileBase(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Course::ConstResourceMaps::GRASSLAND_BP);
    virtual QGraphicsPixmapItem* getSprite();
    virtual void setSprite(QPixmap image);
    bool getRobber();
    bool getTreasure();

    bool setRobber(bool x);
    bool setTreasure(bool x);
private:
    QGraphicsPixmapItem* sprite;
    bool hasRobber;
    bool hasTreasure;
    int treasure;
};
}
#endif // GAMETILEBASE_H
