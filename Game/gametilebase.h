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

/**
 * @brief The GameTileBase class base class for all tiles used in game. Inherited from TileBase
 */
class GameTileBase : public Course::TileBase
{
public:
    GameTileBase(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    /**
     * @brief getSprite
     * @return Qpixmap image to draw buildings to mapwindow
     */
    virtual QPixmap getSprite();
    void updateSprite(QPixmap newSprite);
    virtual void addGameBuilding(const std::shared_ptr<Game::GameBuildingBase>& building);
    bool getRobber(); // if tile contains robber
    bool getTreasure(); // if tile has treasure
    int getHeight(); // tile height
    int getWidth(); // tile width
    std::vector<std::shared_ptr<GameBuildingBase>> buildingsOnTile; // in this game only one building in tile

    bool setRobber(bool x);
    bool setTreasure(bool x);
protected:
    QPixmap sprite;
    bool hasRobber;
    bool hasTreasure;
    int treasure;
    int width;
    int height;
    //std::vector<std::shared_ptr<Course::WorkerBase>> workers;
};
}
#endif // GAMETILEBASE_H
