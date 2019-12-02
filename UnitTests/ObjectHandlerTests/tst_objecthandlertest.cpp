#include <QtTest>
#include <iostream>
#include <QApplication>

// add necessary includes here
#include "gameobjectmanager.h"
#include "gameeventhandler.h"
#include "gametilebase.h"
#include "Workers/noviceworker.h"

class ObjectHandlerTest : public QObject
{
    Q_OBJECT

public:
    ObjectHandlerTest();
    ~ObjectHandlerTest();

private slots:
    void testAddTiles();
    void testAddGameTile();
    void testAddWorker();

};

ObjectHandlerTest::ObjectHandlerTest()
{

}

ObjectHandlerTest::~ObjectHandlerTest()
{

}

void ObjectHandlerTest::testAddTiles()
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
    std::cout<<tiles.size()<<std::endl;
    std::cout<<objManager->getGameObjects().size()<<std::endl;
    QVERIFY(tiles.size() == objManager->getGameObjects().size());
}

void ObjectHandlerTest::testAddGameTile()
{
    /*
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
    }*/

}

void ObjectHandlerTest::testAddWorker()
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


QTEST_APPLESS_MAIN(ObjectHandlerTest)

#include "tst_objecthandlertest.moc"
