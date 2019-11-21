#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <random>
#include "../CourseLib/interfaces/igameeventhandler.h"

namespace Game{

class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler();
    ~GameEventHandler();
    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);
    void endTurn();
    int throwDice();
    void nextTurn();

    //getters
    int getDiceValue();
    int getTurn();
    bool getThrown();
    bool getPlayerMoved();
    bool isMoving();

    //setters
    void setThrown(bool x);
    void setPlayerMoved(bool x);
    void setMoving(bool x);

private:
    bool threw;
    bool moved;
    bool moving;
    int diceValue;
    int turn;
    bool building;
    bool built;
    bool searchedArea;
};
}

#endif // GAMEEVENTHANDLER_H
