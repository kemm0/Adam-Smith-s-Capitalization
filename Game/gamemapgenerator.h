#ifndef GAMEMAPGENERATOR_H
#define GAMEMAPGENERATOR_H

#include "../CourseLib/core/worldgenerator.h"
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "Tiles/grasstile.h"
#include "Tiles/foresttile.h"
#include "Tiles/towntile.h"
#include "Tiles/watertile.h"
#include "Buildings/farmbuilding.h"
#include "Buildings/loggingbuilding.h"
#include "Buildings/fishingbuilding.h"
#include "Workers/noviceworker.h"
#include "Workers/apprenticeworker.h"
#include "Workers/masterworker.h"


namespace Game{

/**
 * @brief The mapCodes enum
 * Name for each integer value that represents a tile type in mapTemplate
 */
enum mapCodes{
    GRASSLAND = 0,
    WATER = 1,
    FOREST = 3,
};

/**
 * @brief The GameMapGenerator class creates new game objects that make up the game world.
 */
class GameMapGenerator: public QObject{
Q_OBJECT
public:
    /**
     * @brief GameMapGenerator
     * @param objManager
     * @param eventHandler
     * @param parent
     */
    GameMapGenerator(std::shared_ptr<GameObjectManager> objManager,
                     std::shared_ptr<GameEventHandler> eventHandler,
                     QObject *parent = nullptr);
    ~GameMapGenerator();
    /**
     * @brief createMapObjects
     * Creates tiles according to their corresponding integer values in mapTemplate matrix.
     */
    void createMapObjects();
    /**
     * @brief createBuilding
     * @param location
     * Creates a building to the tile in the given location.
     */
    void createBuilding(Course::Coordinate location);
    /**
     * @brief getRandomMapCoordinate
     * @return Course::Coordinate, which is random coordinate inside the map
     * Used to generate a random coordinate
     */
    Course::Coordinate getRandomMapCoordinate();
    void setTreasure(int amount);
    void setRobber(int amount);

    /**
     * @brief createGrassTile
     * @param location
     * Creates a new GrassTile to the given location and adds it to object manager
     */
    void createGrassTile(Course::Coordinate location);

    /**
     * @brief createForestTile
     * @param location
     * Creates a new ForestTile to the given location and adds it to object manager
     */
    void createForestTile(Course::Coordinate location);
    /**
     * @brief createWaterTile
     * @param location
     * Creates a new WaterTile to the given location and adds it to object manager
     */
    void createWaterTile(Course::Coordinate location);
    /**
     * @brief createPlayer
     * @param location
     * Creates a new Player character and adds it to object manager
     */
    void createPlayer(Course::Coordinate location);

    /**
     * @brief createWorker
     * @param targetTile
     * Creates a new worker according to the selected worker type in eventHandler and adds it to the given Tile's list of workers.
     */
    void createWorker(std::shared_ptr<GameTileBase> targetTile);

    /**
     * @brief createFarmhouse
     * @param targetTile
     * Creates a new FarmBuilding to the given Tile and adds it to object manager
     */
    void createFarmhouse(std::shared_ptr<GameTileBase> targetTile);

    /**
     * @brief createLoggingcabin
     * @param targetTile
     * Creates a new LoggingBuilding to the given Tile and adds it to object manager
     */
    void createLoggingcabin(std::shared_ptr<GameTileBase> targetTile);

    /**
     * @brief createFishinghut
     * @param targetTile
     * Creates a new FishingBuilding to the given Tile and adds it to object manager
     */
    void createFishinghut(std::shared_ptr<GameTileBase> targetTile);
signals:
    /**
     * @brief gameMessage
     * sends a message (string) to connected slots
     */
    void gameMessage(std::string);

private:
    std::vector<std::vector<int>> mapTemplate; // Map template for current map used
    std::shared_ptr<GameObjectManager> objManager_;
    std::shared_ptr<GameEventHandler> eventHandler_;
    int mapWidth;
    int mapHeight;

};
}

#endif // GAMEMAPGENERATOR_H
