#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "gameeventhandler.h"
#include "gameobjectmanager.h"
#include "Workers/noviceworker.h"
#include "gametilebase.h"
#include "gamebuildingbase.h"

/**
 * @brief The ObjectManagerTest class
 * Tests for Game's GameObjectManager class. Tests for some getters and setters are grouped in a same test case
 */

class ObjectManagerTest : public QObject
{
    Q_OBJECT

public:
    ObjectManagerTest();
    ~ObjectManagerTest();

private slots:
    void testAddTiles();
    void testAddAndGetGameTiles();
    void testAddAndGetWorkers();
    void testAddAndGetGameObjects();
    void testGetTileByCoordinate();
    void testGetTileByID();
    void testGetTilesByCoordinates();
    void testGetGameTileByCoordinate();
    void testAddAndGetBuilding();
    void testGetAndSetPlayer();


};

ObjectManagerTest::ObjectManagerTest()
{

}

ObjectManagerTest::~ObjectManagerTest()
{

}
/**
 * @brief ObjectManagerTest::testAddTiles
 * Tests GameObjectManager's AddTiles()-function
 */
void ObjectManagerTest::testAddTiles()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    std::vector<std::shared_ptr<Course::TileBase> > tiles = {};
    QVERIFY(objManager->getGameObjects().size() == 0);
    for(int i = 0; i<100; i++){
        std::shared_ptr<Course::TileBase> newTile = std::make_shared<Course::TileBase>(Course::Coordinate(i, i*10),
                                                                                       eventHandler,                                                                                       objManager);
        tiles.push_back(newTile);
    }
    objManager->addTiles(tiles);
    QVERIFY(tiles.size() == objManager->getGameObjects().size());
}
/**
 * @brief ObjectManagerTest::testAddAndGetGameTiles
 * Tests GameObjectManager's addGameTile()-function and getGameTiles()-function
 */
void ObjectManagerTest::testAddAndGetGameTiles()
{

    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getGameTiles().size() == 0);
    for(int i = 0; i < 10; i++){
        unsigned int currentSize = objManager->getGameTiles().size();
        std::shared_ptr<Game::GameTileBase> newTile = std::make_shared<Game::GameTileBase>(Course::Coordinate(i,i),
                                                                                       eventHandler,
                                                                                       objManager);
        objManager->addGameTile(newTile);
        QVERIFY(objManager->getGameTiles().size() == currentSize + 1);
    }

}
/**
 * @brief ObjectManagerTest::testAddAndGetWorkers
 * Tests GameObjectManager's addWorker()-function and getWorkers()-function
 */

void ObjectManagerTest::testAddAndGetWorkers()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getGameTiles().size() == 0);
    for(int i = 0; i < 100; i++){
        unsigned int currentSize = objManager->getWorkers().size();
        std::shared_ptr<Game::NoviceWorker> newWorker = std::make_shared<Game::NoviceWorker>(eventHandler,
                                                                                             objManager,
                                                                                             nullptr);
        objManager->addWorker(newWorker);
        QVERIFY(objManager->getWorkers().size() == currentSize + 1);
    }
}

/**
 * @brief ObjectManagerTest::testAddAndGetGameObjects
 * Tests GameObjectManager's addGameObject()-function and getGameObjects()-function
 */

void ObjectManagerTest::testAddAndGetGameObjects()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getGameObjects().size() == 0);
    for(int i = 0; i < 100; i++){
        unsigned int currentSize = objManager->getGameObjects().size();
        std::shared_ptr<Game::NoviceWorker> newWorker = std::make_shared<Game::NoviceWorker>(eventHandler,
                                                                                             objManager,
                                                                                             nullptr);
        objManager->addGameObject(newWorker);
        QVERIFY(objManager->getGameObjects().size() == currentSize + 1);
    }
}

/**
 * @brief ObjectManagerTest::testGetTileByCoordinate
 * Tests GameObjectManager's getTile(Course::Coordinate)-function
 */

void ObjectManagerTest::testGetTileByCoordinate()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getGameTiles().size() == 0);
    for(int i = -50; i < 50; i++){
        Course::Coordinate newCoord(i,i);
        std::shared_ptr<Game::GameTileBase> newTile = std::make_shared<Game::GameTileBase>(newCoord,
                                                                                       eventHandler,
                                                                                       objManager);
        objManager->addGameTile(newTile);
        QVERIFY(objManager->getTile(newCoord)->getCoordinate() == newCoord);
    }
}

/**
 * @brief ObjectManagerTest::testGetTileByID
 * Tests GameObjectManager's getTile(Course::ID)-function
 */

void ObjectManagerTest::testGetTileByID()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getGameTiles().size() == 0);
    for(int i = -50; i < 50; i++){
        Course::Coordinate newCoord(i,i);
        std::shared_ptr<Game::GameTileBase> newTile = std::make_shared<Game::GameTileBase>(newCoord,
                                                                                       eventHandler,
                                                                                       objManager);
        objManager->addGameTile(newTile);
        QVERIFY(objManager->getTile(newTile->ID)->ID == newTile->ID);
    }
}

/**
 * @brief ObjectManagerTest::testGetTilesByCoordinates
 * Tests GameObjectManager's getTiles(std::vector<Course::Coordinate>)-function
 */

void ObjectManagerTest::testGetTilesByCoordinates()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getGameTiles().size() == 0);
    std::vector<Course::Coordinate> coordinates = {};
    for(int i = -50; i < 50; i++){
        Course::Coordinate newCoord(i,i);
        std::shared_ptr<Game::GameTileBase> newTile = std::make_shared<Game::GameTileBase>(newCoord,
                                                                                       eventHandler,
                                                                                       objManager);
        objManager->addGameTile(newTile);
        coordinates.push_back(newCoord);
        QVERIFY(objManager->getTile(newCoord)->getCoordinate() == newCoord);
    }
    std::vector<std::shared_ptr<Course::TileBase>> tiles = objManager->getTiles(coordinates);
    for(unsigned int i = 0; i < coordinates.size();i++){
        QVERIFY(tiles.at(i)->getCoordinate() == coordinates.at(i));
    }
}

/**
 * @brief ObjectManagerTest::testGetGameTileByCoordinate
 * Tests GameObjectManager's getGameTile(Course::Coordinate)-function
 */
void ObjectManagerTest::testGetGameTileByCoordinate()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getGameTiles().size() == 0);
    for(int i = -50; i < 50; i++){
        Course::Coordinate newCoord(i,i);
        std::shared_ptr<Game::GameTileBase> newTile = std::make_shared<Game::GameTileBase>(newCoord,
                                                                                       eventHandler,
                                                                                       objManager);
        objManager->addGameTile(newTile);
        QVERIFY(objManager->getGameTile(newCoord)->getCoordinate() == newCoord);
    }
}

/**
 * @brief ObjectManagerTest::testAddAndGetBuilding
 * Tests GameObjectManager's addBuilding()-function and getBuildings()-function
 */

void ObjectManagerTest::testAddAndGetBuilding()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    QVERIFY(objManager->getBuildings().size() == 0);
    for(int i = 0; i < 100; i++){
        unsigned int currentSize = objManager->getBuildings().size();
        std::shared_ptr<Game::GameBuildingBase> newBuilding = std::make_shared<Game::GameBuildingBase>(eventHandler,
                                                                                             objManager,
                                                                                             nullptr);
        objManager->addBuilding(newBuilding);
        QVERIFY(objManager->getBuildings().size() == currentSize + 1);
    }
}

/**
 * @brief ObjectManagerTest::testGetAndSetPlayer
 * Tests GameObjectManager's setPlayer()-function and getPlayer()-function
 */

void ObjectManagerTest::testGetAndSetPlayer()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    for(int i = -50; i < 50; i++){
        Course::Coordinate newCoord(i,i);
        std::shared_ptr<Game::Player> newPlayer = std::make_shared<Game::Player>(newCoord,"Adam Smith",eventHandler,objManager);
        objManager->setPlayer(newPlayer);
        QVERIFY(objManager->getPlayer()->ID == newPlayer->ID);
    }
}


QTEST_MAIN(ObjectManagerTest)

#include "tst_objectmanagertest.moc"
