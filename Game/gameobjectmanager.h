#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "../CourseLib/interfaces/iobjectmanager.h"
#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/core/coordinate.h"
#include "player.h"



class GameObjectManager: public Course::iObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();
    void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);

    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates) = 0;
    void loadFromMap(std::vector<std::vector<int>>& objectMap);

private:
    std::vector<Course::GameObject> gameObjects;
    //Player* player1;
};

#endif // GAMEOBJECTMANAGER_H
