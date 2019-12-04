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

/**
 * @brief The gameOverState enum
 * different endings for the game
 */
enum gameOverState{
    GOT_RICH,
    LATE,
    BANKRUPT,
    NO_PROFIT,
    NO_TREASURE
};

/**
 * @brief The GameEventHandler class interface inherited from iGameEventHandler.
 */
class GameEventHandler : public QObject, public Course::iGameEventHandler
{
Q_OBJECT
public:
    /**
     * @brief GameEventHandler
     * @param manager points to the game's object manager
     * @param parent
     */
    GameEventHandler(std::shared_ptr<GameObjectManager> manager,
                     QObject *parent = nullptr);
    ~GameEventHandler();
    /**
     * @brief modifyResource
     * @param player
     * @param resource
     * @param amount
     * @return true, if modification was successful, false if not
     * used to modify player's one resource by given amount
     */
    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);
    /**
     * @brief modifyResources
     * @param player
     * @param resources
     * @return true, if modification was successful, false if not
     * used to add or substract player's resources
     */
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);
    /**
     * @brief endTurn increases turn count
     */
    void endTurn();
    /**
     * @brief throwDice
     * @return dice number
     */
    int throwDice();


    //getters

    /**
     * @brief getDiceValue
     * @return the value of the dice
     */
    int getDiceValue();
    /**
     * @brief getTurn
     * @return current turn
     */
    int getTurn();
    /**
     * @brief getThrown
     * @return true, if player has thrown, false if not
     */
    bool getThrown();
    /**
     * @brief getPlayerMoved
     * @return true, if player has moved, false if not
     */
    bool getPlayerMoved();
    /**
     * @brief isMoving
     * @return true, if player is moving, false if not
     */
    bool isMoving();
    /**
     * @brief isBuilding
     * @return true, if player is building, false if not
     */
    bool isBuilding();
    /**
     * @brief getPlayerBuilt
     * @return true, if player has built, false if not
     */
    bool getPlayerBuilt();
    /**
     * @brief getPlayerSearched
     * @return true, if player has searched, false if not
     */
    bool getPlayerSearched();
    /**
     * @brief isSearching
     * @return true, if player is searching, false if not
     */
    bool isSearching();
    /**
     * @brief isHiring
     * @return true, if player is hiring, false if not
     */
    bool isHiring();
    /**
     * @brief getHired
     * @return true, if player has hired, false if not
     */
    bool getHired();

    /**
     * @brief getWorkerType
     * @return the Type of worker that has been selected
     */
    std::string getWorkerType();


    //setters

    /**
     * @brief setThrown
     * @param x
     */
    void setThrown(bool x);
    /**
     * @brief setPlayerMoved
     * @param x
     */
    void setPlayerMoved(bool x);
    /**
     * @brief setPlayerBuilt
     * @param x
     */
    void setPlayerBuilt(bool x);
    /**
     * @brief setMoving
     * @param x
     */
    void setMoving(bool x);
    /**
     * @brief setBuildingState
     * @param x
     */
    void setBuildingState(bool x);
    /**
     * @brief setSelectedBuildingType
     * @param buildingType
     */
    void setSelectedBuildingType(std::string buildingType);
    /**
     * @brief setSearching
     * @param x
     */
    void setSearching(bool x);
    /**
     * @brief setPlayerSearched
     * @param x
     */
    void setPlayerSearched(bool x);
    /**
     * @brief setPlayerHired
     * @param x
     */
    void setPlayerHired(bool x);
    /**
     * @brief setHiring
     * @param x
     */
    void setHiring(bool x);
    /**
     * @brief setWorkerType
     * @param type
     */
    void setWorkerType(std::string type);

signals:
    /**
     * @brief gameMessage
     * passes a message (string) to connected components
     */
    void gameMessage(std::string);
    /**
     * @brief gameOver
     * passes information of the state that the game ended with
     */
    void gameOver(gameOverState);

private:
    bool threw;
    bool moved;
    bool moving;
    int diceValue;
    int turn;
    int maxTurns;
    bool building;
    bool built;
    bool searching;
    bool searchedArea;
    bool hiring;
    bool hired;
    std::shared_ptr<GameObjectManager> objManager;
    std::string workertype;
};
}

#endif // GAMEEVENTHANDLER_H
