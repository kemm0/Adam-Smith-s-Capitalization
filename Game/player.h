#ifndef PLAYER_H
#define PLAYER_H

#include "../CourseLib/core/playerbase.h"
#include "../CourseLib/core/gameobject.h"
#include "QPixmap"
#include "gameresourcemap.h"
#include "gameresourcemap.h"
namespace Game{
class GameEventHandler;
class GameObjectManager;
class GameBuildingBase;
class GameTileBase;

/**
 * @brief The Player class used for player instance
 */

class Player :

        public QObject,
        public Course::PlayerBase,
        public Course::GameObject

{

Q_OBJECT

public:
    Player(const Course::Coordinate &coord,
           const std::string& name = "Adam Smith",
           std::shared_ptr<Game::GameEventHandler> handler = nullptr,
           std::shared_ptr<Game::GameObjectManager> manager = nullptr,
           const std::vector<std::shared_ptr<Course::GameObject> > objects = {},
           QObject *parent = nullptr);
    ~Player();
    QPixmap getSprite(); // QPixmap used to draw player
    Course::ResourceMap getResources();
    void modifyResources(Course::ResourceMap rmap);
    void getProfit();
    int getStartingMoney();
    bool hasTreasure();
    void setTreasure(bool t);

signals:
    void currentMoney(int amount);

private:
        QPixmap sprite;
        int money;
        Course::ResourceMap resources;
        bool treasure;
};
}

#endif // PLAYER_H
