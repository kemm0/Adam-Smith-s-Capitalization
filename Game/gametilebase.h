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
 * @brief The GameTileBase class base class for all tiles used in game.
 */
class GameTileBase : public Course::TileBase
{
public:
    /**
     * @brief GameTileBase
     * @param location
     * @param eventhandler
     * @param objectmanager
     * @param max_build maximum amount of buildings that can be placed on
     *  the tile
     * @param max_work maximum amount of workers that can be placed on the tile
     * @param production
     */
    GameTileBase(const Course::Coordinate& location,
              const std::shared_ptr<GameEventHandler>& eventhandler,
              const std::shared_ptr<GameObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Game::ConstGameResourceMap::TILE_BP);
    /**
     * @brief getSprite
     * @return Qpixmap image to draw buildings to map scene
     */
    virtual QPixmap getSprite();
    /**
     * @brief updateSprite
     * @param newSprite
     * sets the sprite image to the given one
     */
    void updateSprite(QPixmap newSprite);
    /**
     * @brief getRobber
     * @return true, if tile has robber, false if not
     */
    bool getRobber();
    /**
     * @brief getTreasure
     * @return true, if tile has treasure, false if not
     */
    bool getTreasure();
    /**
     * @brief getHeight
     * @return height of the sprite image
     */
    int getHeight();
    /**
     * @brief getWidth
     * @return width of the sprite image
     */
    int getWidth();

    /**
     * @brief setRobber if robber == true, tile will have a robber
     * @param robber
     * @return
     */
    void setRobber(bool robber);
    /**
     * @brief setTreasure if treasure == true, tile will have a trasure
     * @param treasure
     * @return
     */
    void setTreasure(bool treasure);
protected:
    QPixmap sprite;
    bool hasRobber;
    bool hasTreasure;
    int treasure;
    int width;
    int height;
};
}
#endif // GAMETILEBASE_H
