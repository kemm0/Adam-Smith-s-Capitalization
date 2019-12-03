#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H


#include "../CourseLib/interfaces/iobjectmanager.h"
#include "../CourseLib/tiles/tilebase.h"
#include "../CourseLib/core/coordinate.h"
#include "player.h"
#include "../CourseLib/core/worldgenerator.h"
//#include "gameeventhandler.h"

namespace Game{

class GameTileBase;
class FarmBuilding;
class FishingBuilding;
class LoggingBuilding;


class GameObjectManager: public QObject, public Course::iObjectManager
{
Q_OBJECT
public:
    /**
     * @brief GameObjectManager
     * @param parent
     */
    GameObjectManager(QObject *parent = nullptr);
    ~GameObjectManager();
    void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);
    /**
     * @brief addGameTile adds tile to gametile-vector
     */
    void addGameTile(std::shared_ptr<Game::GameTileBase> tile);

    std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);
    /**
     * @brief getGameObjects
     * @return vector containing all gameobjects
     */
    std::vector<std::shared_ptr<Course::GameObject>> getGameObjects();

    /**
     * @brief getTile
     * @param id
     * @return shared pointer that points to the tile that has the given ID
     * Use to get a tile with a certain ID
     */
    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    /**
     * @brief getTiles
     * @param coordinates
     * @return vector of shared pointers that point to the tiles with given coordinates
     * Use to get the tiles in an area or multiple locations
     */
    std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);
    /**
     * @brief getGameTiles
     * @return returns vector containing all gametiles
     */
    std::vector<std::shared_ptr<Game::GameTileBase>> getGameTiles();
    /**
     * @brief getGameTile returns the tile in given coordinates
     */
    std::shared_ptr<Game::GameTileBase> getGameTile(const Course::Coordinate& coordinate);
    /**
     * @brief setPlayer used from mapgenerator to set player
     * @param player
     */
    void setPlayer(std::shared_ptr<Game::Player> player);
    /**
     * @brief getPlayer used in different classes to get players pointer to get to players attributes
     * @return pointer to player
     */
    std::shared_ptr<Game::Player> getPlayer();
    /**
     * @brief getWorkers
     * @return vector with all the workers
     */
    std::vector<std::shared_ptr<Course::WorkerBase>> getWorkers();
    void addWorker(std::shared_ptr<Course::WorkerBase> worker);
    void addGameObject(std::shared_ptr<Course::GameObject> object);

private:
    std::vector<std::shared_ptr<Game::GameBuildingBase>> buildings;
    std::vector<std::shared_ptr<Course::WorkerBase>> workers;
    std::vector<std::shared_ptr<Course::GameObject>> gameObjects_;
    std::vector<std::shared_ptr<Game::GameTileBase>> gameTiles;
    std::shared_ptr<Game::Player> player_;
};

}

#endif // GAMEOBJECTMANAGER_H
