#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "../CourseLib/interfaces/iobjectmanager.h"
#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/core/coordinate.h"
#include "player.h"

namespace Game{

class GameObjectManager: public Course::iObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();
    void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);
    void addTile(std::shared_ptr<Course::TileBase> tile);

    std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);

    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);
    void loadFromMap(std::vector<std::vector<int>>& objectMap);

private:
    std::vector<Course::GameObject> gameObjects_;
    std::vector<Course::TileBase> mapTiles_;
    std::shared_ptr<Game::Player> player_;
    //Player* player1;
};

}

#endif // GAMEOBJECTMANAGER_H
