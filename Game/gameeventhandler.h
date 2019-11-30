#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <random>
#include "../CourseLib/interfaces/igameeventhandler.h"
#include "gameobjectmanager.h"
#include "gameresourcemap.h"
#include "QMessageBox"


namespace Game{

class GameTileBase;
class GameBuildingBase;
class FarmBuilding;

class GameEventHandler : public QObject, public Course::iGameEventHandler
{
Q_OBJECT
public:
    GameEventHandler(std::shared_ptr<GameObjectManager> manager, QObject *parent = nullptr);
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
    void checkIfOutOfMoney(std::map<Course::BasicResource, int> amount);


    //getters
    int getDiceValue();
    int getTurn();
    bool getThrown();
    bool getPlayerMoved();
    bool isMoving();
    bool isBuilding();
    bool getPlayerBuilt();
    bool getPlayerSearched();
    bool isSearching();
    bool isHiring();
    bool getHired();
    std::string getSelectedBuildingType();
    std::string getWorkerType();


    //setters
    void setThrown(bool x);
    void setPlayerMoved(bool x);
    void setPlayerBuilt(bool x);
    void setMoving(bool x);
    void setBuildingState(bool x);
    void setSelectedBuildingType(std::string buildingType);
    void setSearching(bool x);
    void setPlayerSearched(bool x);
    void setPlayerHired(bool x);
    void setHiring(bool x);
    void setWorkerType(std::string type);

signals:
    void gameOver(bool ranOutOfMoney);



private:
    bool threw;
    bool moved;
    bool moving;
    int diceValue;
    int turn;
    bool building;
    bool built;
    bool searching;
    bool searchedArea;
    bool hiring;
    bool hired;
    std::string selectedBuildingType;
    std::shared_ptr<GameObjectManager> objManager;
    std::vector<std::shared_ptr<GameBuildingBase>> ownedBuildings;
    std::string workertype;
};
}

#endif // GAMEEVENTHANDLER_H
