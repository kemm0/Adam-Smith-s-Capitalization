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
    int getDiceValue();
    int getTurn();
    bool threw;
    bool moved;
private:
    int diceValue;
    int turn;
};
}

#endif // GAMEEVENTHANDLER_H
