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
    }
}

QTEST_APPLESS_MAIN(EventHandlerTest)

#include "tst_eventhandlertest.moc"
