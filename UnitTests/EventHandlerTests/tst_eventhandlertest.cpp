#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "gameeventhandler.h"
#include "gameobjectmanager.h"
#include "gameresourcemap.h"

/**
 * @brief The EventHandlerTest class
 * Tests the funtions of Game's GameEventHandler class.
 * Tests for some getters and setters are grouped in a same test case
 */

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
    void testModifyResources();
    void testModifyResource();


};

EventHandlerTest::EventHandlerTest()
{

}

EventHandlerTest::~EventHandlerTest()
{

}

/**
 * @brief EventHandlerTest::testDiceThrow
 * Tests GameEventHandler's throwDice()-function.
 * Checks if the values are between 1 and 6
 */
void EventHandlerTest::testDiceThrow()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);
    for(int i = 0; i < 1000; i++){
        int diceNumber = eventHandler->throwDice();
        QVERIFY(diceNumber<=6 && diceNumber>=1);
        QVERIFY(eventHandler->getDiceValue() == diceNumber);
    }
}

/**
 * @brief EventHandlerTest::testEndTurn
 * Tests GameEventHandler's endTurn()-function.
 * All statuses should be false at the end of the turn
 * and the turn number should be 1 higher at start of the next turn
 */
void EventHandlerTest::testEndTurn(){
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

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

// Getter and Setter function tests

/**
 * @brief EventHandlerTest::testGetTurn
 * Tests GameEventHandler's getTurn()-function.
 */
void EventHandlerTest::testGetTurn()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    for(int i = 1; i < 1000; i++){
        int turn = eventHandler->getTurn();
        QVERIFY(turn == i);
        eventHandler->endTurn();
    }
}

/**
 * @brief EventHandlerTest::testThrownStatus
 * Tests GameEventHandler's getThrown() and setThrown()-functions.
 */
void EventHandlerTest::testThrownStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setThrown(true);
    QVERIFY(eventHandler->getThrown() == true);
    eventHandler->setThrown(false);
    QVERIFY(eventHandler->getThrown() == false);
}

/**
 * @brief EventHandlerTest::testPlayerMovedStatus
 * Tests GameEventHandler's getPlayerMoved()-function and
 * setPlayerMoved()-function.
 */
void EventHandlerTest::testPlayerMovedStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setPlayerMoved(true);
    QVERIFY(eventHandler->getPlayerMoved() == true);
    eventHandler->setPlayerMoved(false);
    QVERIFY(eventHandler->getPlayerMoved() == false);
}

/**
 * @brief EventHandlerTest::testPlayerMovingStatus
 * Tests GameEventHandler's isMoving() and setMoving()-functions.
 */
void EventHandlerTest::testPlayerMovingStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setMoving(true);
    QVERIFY(eventHandler->isMoving() == true);
    eventHandler->setMoving(false);
    QVERIFY(eventHandler->isMoving() == false);
}

/**
 * @brief EventHandlerTest::testPlayerBuildingStatus
 * Tests GameEventHandler's isBuilding() and setBuildingState()-functions.
 */

void EventHandlerTest::testPlayerBuildingStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setBuildingState(true);
    QVERIFY(eventHandler->isBuilding() == true);
    eventHandler->setBuildingState(false);
    QVERIFY(eventHandler->isBuilding() == false);
}

/**
 * @brief EventHandlerTest::testPlayerBuiltStatus
 *  Tests GameEventHandler's getPlayerBuilt() and setPlayerBuilt()-functions.
 */

void EventHandlerTest::testPlayerBuiltStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setPlayerBuilt(true);
    QVERIFY(eventHandler->getPlayerBuilt() == true);
    eventHandler->setPlayerBuilt(false);
    QVERIFY(eventHandler->getPlayerBuilt() == false);
}

/**
 * @brief EventHandlerTest::testPlayerSearchedStatus
 *  Tests GameEventHandler's getPlayerSearched() and
 *  setPlayerSearched()-functions.
 */

void EventHandlerTest::testPlayerSearchedStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setPlayerSearched(true);
    QVERIFY(eventHandler->getPlayerSearched() == true);
    eventHandler->setPlayerSearched(false);
    QVERIFY(eventHandler->getPlayerSearched() == false);
}

/**
 * @brief EventHandlerTest::testPlayerSearchingStatus
 *  Tests GameEventHandler's setSearching() and isSearching()-functions.
 */
void EventHandlerTest::testPlayerSearchingStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setSearching(true);
    QVERIFY(eventHandler->isSearching() == true);
    eventHandler->setSearching(false);
    QVERIFY(eventHandler->isSearching() == false);
}

/**
 * @brief EventHandlerTest::testPlayerHiringStatus
 *  Tests GameEventHandler's isHiring() and setHiring()-functions.
 */
void EventHandlerTest::testPlayerHiringStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setHiring(true);
    QVERIFY(eventHandler->isHiring() == true);
    eventHandler->setHiring(false);
    QVERIFY(eventHandler->isHiring() == false);
}

/**
 * @brief EventHandlerTest::testPlayerHiredStatus
 *  Tests GameEventHandler's setPlayerHired() and getHired()-functions.
 */
void EventHandlerTest::testPlayerHiredStatus()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    eventHandler->setPlayerHired(true);
    QVERIFY(eventHandler->getHired() == true);
    eventHandler->setPlayerHired(false);
    QVERIFY(eventHandler->getHired() == false);
}

/**
 * @brief EventHandlerTest::testSelectedWorkerType
 * Tests GameEventHandler's setWorkerType() and getWorkerType()-functions.
 */
void EventHandlerTest::testSelectedWorkerType()
{
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);
    std::string novice = "novice worker";
    std::string apprentice = "apprentice worker";
    std::string master = "master worker";

    eventHandler->setWorkerType(novice);
    QVERIFY(eventHandler->getWorkerType() == novice);

    eventHandler->setWorkerType(apprentice);
    QVERIFY(eventHandler->getWorkerType() == apprentice);

    eventHandler->setWorkerType(master);
    QVERIFY(eventHandler->getWorkerType() == master);
}

void EventHandlerTest::testModifyResources()
{
    Course::Coordinate location(0,0);
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();

    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    std::shared_ptr<Game::Player> player1 = std::make_shared<Game::Player>(
                location,"James",eventHandler,objManager);

    objManager->setPlayer(player1);
    QVERIFY(player1->getResources() == Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES);
    eventHandler->modifyResources(
                objManager->getPlayer(),
                Game::ConstGameResourceMap::FARM_BUILD_COST);
    QVERIFY(objManager->getPlayer()->getResources() == Course::mergeResourceMaps(
                Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES,
                Game::ConstGameResourceMap::FARM_BUILD_COST));

    std::shared_ptr<Game::Player> player2 = std::make_shared<Game::Player>(
                location,"James",eventHandler,objManager);
    objManager->setPlayer(player2);
    QVERIFY(objManager->getPlayer()->getResources() == Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES);

    eventHandler->modifyResources(
                objManager->getPlayer(),
                Game::ConstGameResourceMap::TREASURE);
    QVERIFY(objManager->getPlayer()->getResources() == Course::mergeResourceMaps(
                Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES,
                Game::ConstGameResourceMap::TREASURE));

}

void EventHandlerTest::testModifyResource()
{
    Course::Coordinate location(0,0);
    std::shared_ptr<Game::GameObjectManager> objManager = std::make_shared<
            Game::GameObjectManager>();

    std::shared_ptr<Game::GameEventHandler> eventHandler = std::make_shared<
            Game::GameEventHandler>(objManager);

    std::shared_ptr<Game::Player> player1 = std::make_shared<Game::Player>(
                location,"James",eventHandler,objManager);

    objManager->setPlayer(player1);
    QVERIFY(player1->getResources() == Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES);
    eventHandler->modifyResource(
                objManager->getPlayer(),
                Course::MONEY,100);
    QVERIFY(objManager->getPlayer()->getResources().at(Course::MONEY)==(
                Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES.at(
                    Course::MONEY)+100));

    std::shared_ptr<Game::Player> player2 = std::make_shared<Game::Player>(
                location,"James",eventHandler,objManager);
    objManager->setPlayer(player2);

    QVERIFY(player2->getResources() == Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES);
    eventHandler->modifyResource(
                objManager->getPlayer(),
                Course::MONEY,-100);
    QVERIFY(objManager->getPlayer()->getResources().at(Course::MONEY)==(
                Game::ConstGameResourceMap::PLAYER_STARTING_RESOURCES.at(
                    Course::MONEY)-100));
}

QTEST_MAIN(EventHandlerTest)

#include "tst_eventhandlertest.moc"
