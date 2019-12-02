#include <QtTest>

// add necessary includes here
#include "gameeventhandler.h"
#include "gameobjectmanager.h"

class EventHandlerTest : public QObject
{
    Q_OBJECT

public:
    EventHandlerTest();
    ~EventHandlerTest();

private slots:
    void testDiceThrow();
    void testEndTurn();
    void testGetTurn();
    void testThrownStatus();
    void testPlayerMovedStatus();
    void testPlayerMovingStatus();
    void testPlayerBuildingStatus();
    void testPlayerBuiltStatus();
    void testPlayerSearchedStatus();
    void testPlayerSearchingStatus();
    void testPlayerHiringStatus();
    void testPlayerHiredStatus();
    void testSelectedWorkerType();


};

EventHandlerTest::EventHandlerTest()
{

}

EventHandlerTest::~EventHandlerTest()
{

}

void EventHandlerTest::testDiceThrow()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    for(int i = 0; i < 1000; i++){
        int diceNumber = eventHandler->throwDice();
        QVERIFY(diceNumber<=6 && diceNumber>=1);
        QVERIFY(eventHandler->getDiceValue() == diceNumber);
    }
}
void EventHandlerTest::testEndTurn(){
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    for(int i = 0; i < 1000; i++){
        int currentTurn = eventHandler->getTurn();
        eventHandler->endTurn();
        int nextTurn = eventHandler->getTurn();

        QVERIFY(nextTurn == currentTurn+1);
        QVERIFY(eventHandler->getThrown() == false);
        QVERIFY(eventHandler->getPlayerMoved() == false);
        QVERIFY(eventHandler->isMoving() == false);
        QVERIFY(eventHandler->isBuilding() == false);
        QVERIFY(eventHandler->getPlayerBuilt() == false);
        QVERIFY(eventHandler->isSearching() == false);
        QVERIFY(eventHandler->getPlayerSearched() == false);
        QVERIFY(eventHandler->isHiring() == false);
        QVERIFY(eventHandler->getHired() == false);
    }
}

void EventHandlerTest::testGetTurn()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);
    for(int i = 1; i < 1000; i++){
        int turn = eventHandler->getTurn();
        QVERIFY(turn == i);
        eventHandler->endTurn();
    }
}

void EventHandlerTest::testThrownStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setThrown(true);
    QVERIFY(eventHandler->getThrown() == true);
    eventHandler->setThrown(false);
    QVERIFY(eventHandler->getThrown() == false);
}

void EventHandlerTest::testPlayerMovedStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setPlayerMoved(true);
    QVERIFY(eventHandler->getPlayerMoved() == true);
    eventHandler->setPlayerMoved(false);
    QVERIFY(eventHandler->getPlayerMoved() == false);
}

void EventHandlerTest::testPlayerMovingStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setMoving(true);
    QVERIFY(eventHandler->isMoving() == true);
    eventHandler->setMoving(false);
    QVERIFY(eventHandler->isMoving() == false);
}

void EventHandlerTest::testPlayerBuildingStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setBuildingState(true);
    QVERIFY(eventHandler->isBuilding() == true);
    eventHandler->setBuildingState(false);
    QVERIFY(eventHandler->isBuilding() == false);
}

void EventHandlerTest::testPlayerBuiltStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setPlayerBuilt(true);
    QVERIFY(eventHandler->getPlayerBuilt() == true);
    eventHandler->setPlayerBuilt(false);
    QVERIFY(eventHandler->getPlayerBuilt() == false);
}

void EventHandlerTest::testPlayerSearchedStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setPlayerSearched(true);
    QVERIFY(eventHandler->getPlayerSearched() == true);
    eventHandler->setPlayerSearched(false);
    QVERIFY(eventHandler->getPlayerSearched() == false);
}

void EventHandlerTest::testPlayerSearchingStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setSearching(true);
    QVERIFY(eventHandler->isSearching() == true);
    eventHandler->setSearching(false);
    QVERIFY(eventHandler->isSearching() == false);
}

void EventHandlerTest::testPlayerHiringStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setHiring(true);
    QVERIFY(eventHandler->isHiring() == true);
    eventHandler->setHiring(false);
    QVERIFY(eventHandler->isHiring() == false);
}

void EventHandlerTest::testPlayerHiredStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<Game::GameEventHandler>(objManager);

    eventHandler->setPlayerHired(true);
    QVERIFY(eventHandler->getHired() == true);
    eventHandler->setPlayerHired(false);
    QVERIFY(eventHandler->getHired() == false);
}

void EventHandlerTest::testSelectedWorkerType()
{

}

QTEST_APPLESS_MAIN(EventHandlerTest)

#include "tst_eventhandlertest.moc"
