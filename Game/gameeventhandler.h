#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <random>
#include "../CourseLib/interfaces/igameeventhandler.h"
#include "gameobjectmanager.h"
#include "gameresourcemap.h"

namespace Game{

class GameTileBase;
class GameBuildingBase;
class FarmBuilding;

class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler(std::shared_ptr<GameObjectManager> manager);
    ~GameEventHandler();
    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);
    void endTurn();
    int throwDice();
    void nextTurn();
    int searchArea(std::vector<std::shared_ptr<Game::GameTileBase> > area);
    void createBuilding(Course::Coordinate location);

    //getters
    int getDiceValue();
    int getTurn();
    bool getThrown();
    bool getPlayerMoved();
    bool isMoving();
    bool isBuilding();
    std::string getSelectedBuildingType();

    //setters
    void setThrown(bool x);
    void setPlayerMoved(bool x);
    void setMoving(bool x);
    void setBuildingState(bool x);
    void setSelectedBuildingType(std::string buildingType);

private:
    bool threw;
    bool moved;
    bool moving;
    int diceValue;
    int turn;
    bool building;
    bool built;
    bool searchedArea;
    std::string selectedBuildingType;
    std::shared_ptr<GameObjectManager> objManager;
};
}

#endif // GAMEEVENTHANDLER_H
