#ifndef PLAYER_H
#define PLAYER_H

#include "../CourseLib/core/playerbase.h"
#include "../CourseLib/core/gameobject.h"
#include "QPixmap"
#include "gameresourcemap.h"
namespace Game{
class GameEventHandler;
class GameObjectManager;
class GameBuildingBase;

/**
 * @brief The Player class used for player instance
 */

class GameTileBase;

class Player : public Course::PlayerBase, public Course::GameObject

{
public:
    Player(const Course::Coordinate &coord,
           const std::string& name = "Adam Smith",
           std::shared_ptr<Game::GameEventHandler> handler = nullptr,
           std::shared_ptr<Game::GameObjectManager> manager = nullptr,
           const std::vector<std::shared_ptr<Course::GameObject> > objects = {});
    ~Player();
    QPixmap getSprite(); // QPixmap used to draw player
    int getMoney(); // counts money
    void setMoney(std::map<Course::BasicResource, int>); // adds or subtracts money
    int getStartingMoney();

private:
        QPixmap sprite;
        int money;
        int startingMoney;

};
}

#endif // PLAYER_H
